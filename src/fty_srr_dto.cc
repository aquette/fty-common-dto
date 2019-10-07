/*  =========================================================================
    fty_srr_dto - Fty srr dto

    Copyright (C) 2014 - 2018 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

/*
@header
    fty_srr_dto - Fty srr dto
@discuss
@end
*/

#include "fty_common_dto_classes.h"

namespace dto 
{
    namespace srr 
    {

        /**
         * SRR request object
         * @param data
         * @param object
         */
        void operator<<(messagebus::UserData &data, const SrrQueryDto &object)
        {
            data.push_back(object.action);
            data.push_back(object.data);
        }

        void operator>>(messagebus::UserData &inputData, SrrQueryDto &object)
        {
            auto action = inputData.front();
            inputData.pop_front();
            auto data = inputData.front();
            inputData.pop_front();
            object = SrrQueryDto(action, data);
        }

        /**
         * All features list object threat by SRR
         * @param data
         * @param object
         */
        void operator<<(messagebus::UserData &data, const SrrFeaturesListDto &object)
        {
            for (const auto &dto : object.featuresList)
            {
                data.push_back(dto);
            }
        }

        void operator>> (messagebus::UserData &inputData, SrrFeaturesListDto &object) 
        {
            for (const auto &data : inputData)
            {
                object.featuresList.push_back(data);
            }
            inputData.clear();
        }

        /**
         * SRR response object
         * @param data
         * @param object
         */
        void operator<<(messagebus::UserData &data, const SrrResponseDto &object)
        {
            data.push_back(object.name);
            data.push_back(object.status);
            data.push_back(object.error);
        }

        void operator>>(messagebus::UserData &inputData, SrrResponseDto &object)
        {
            auto name = inputData.front();
            inputData.pop_front();
            auto status = inputData.front();
            inputData.pop_front();
            auto error = inputData.front();
            inputData.pop_front();
            object = SrrResponseDto(name, status, error);
        }

        /**
         * List of SrrResponseDto object with a global status
         * @param data
         * @param object
         */
        void operator<< (messagebus::UserData &data, const SrrResponseDtoList &object) 
        {
            data.push_back(object.status);
            for (auto &srrResponseDto : object.responseList)
            {
                data << srrResponseDto;
            }
        }

        void operator>> (messagebus::UserData &inputData, SrrResponseDtoList &object) {
            object.status = inputData.front();
            inputData.pop_front();
            while(!inputData.empty())
            {
                SrrResponseDto currentDto;
                inputData >> currentDto;
                object.responseList.push_back(currentDto);
            }
        }
    }
}