/*
    Part of Grbl_ESP32
    2021 -  Stefan de Bruijn

    Grbl_ESP32 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Grbl_ESP32 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Grbl_ESP32.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "../Pin.h"
#include "HandlerBase.h"

#include <vector>

namespace Configuration {
    class Configurable;

    class AfterParse : public HandlerBase {
        AfterParse(const AfterParse&) = delete;
        AfterParse& operator=(const AfterParse&) = delete;

        std::vector<const char*> _path;

    protected:
        void        enterSection(const char* name, Configurable* value) override;
        bool        matchesUninitialized(const char* name) override { return false; }
        HandlerType handlerType() override { return HandlerType::AfterParse; }

    public:
        AfterParse() = default;

        void item(const char* name, Setting<bool>& value) override {}
        void item(const char* name, Setting<int32_t>& value, int32_t minValue, int32_t maxValue) override {}
        void item(const char* name, Setting<float>& value, float minValue, float maxValue) override {}
        void item(const char* name, Setting<std::vector<speedEntry>>& value) override {}
        void item(const char* name, Setting<UartData>& wordLength, Setting<UartParity>& parity, Setting<UartStop>& stopBits) override {}
        void item(const char* name, Setting<StringRange>& value, int minLength, int maxLength) override {}
        void item(const char* name, Setting<Pin>& value) override {}
        void item(const char* name, Setting<IPAddress>& value) override {}
        void item(const char* name, Setting<int>& value, EnumItem* e) override {}
    };
}
