/*
 * Copyright (C) 2016 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(APPLE_PAY)

#include "ApplePayPaymentTiming.h"
#include "ApplePayRecurringPaymentDateUnit.h"
#include <optional>
#include <wtf/WallTime.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

struct ApplePayLineItem final {
    enum class Type : bool {
        Pending,
        Final,
    };

    Type type { Type::Final };
    String label;
    String amount;

    ApplePayPaymentTiming paymentTiming { ApplePayPaymentTiming::Immediate };

#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
    WallTime recurringPaymentStartDate { WallTime::nan() };
    ApplePayRecurringPaymentDateUnit recurringPaymentIntervalUnit { ApplePayRecurringPaymentDateUnit::Month };
    unsigned recurringPaymentIntervalCount = 1;
    WallTime recurringPaymentEndDate { WallTime::nan() };
#endif

#if ENABLE(APPLE_PAY_DEFERRED_LINE_ITEM)
    WallTime deferredPaymentDate { WallTime::nan() };
#endif

#if ENABLE(APPLE_PAY_AUTOMATIC_RELOAD_LINE_ITEM)
    String automaticReloadPaymentThresholdAmount; /* required */
#endif

    template<class Encoder> void encode(Encoder&) const;
    template<class Decoder> static std::optional<ApplePayLineItem> decode(Decoder&);
};

template<class Encoder>
void ApplePayLineItem::encode(Encoder& encoder) const
{
    encoder << type;
    encoder << label;
    encoder << amount;
    encoder << paymentTiming;
#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
    encoder << recurringPaymentStartDate;
    encoder << recurringPaymentIntervalUnit;
    encoder << recurringPaymentIntervalCount;
    encoder << recurringPaymentEndDate;
#endif
#if ENABLE(APPLE_PAY_DEFERRED_LINE_ITEM)
    encoder << deferredPaymentDate;
#endif
#if ENABLE(APPLE_PAY_AUTOMATIC_RELOAD_LINE_ITEM)
    encoder << automaticReloadPaymentThresholdAmount;
#endif
}

template<class Decoder>
std::optional<ApplePayLineItem> ApplePayLineItem::decode(Decoder& decoder)
{
#define DECODE(name, type) \
    std::optional<type> name; \
    decoder >> name; \
    if (!name) \
        return std::nullopt; \

    DECODE(type, Type)
    DECODE(label, String)
    DECODE(amount, String)
    DECODE(paymentTiming, ApplePayPaymentTiming)
#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
    DECODE(recurringPaymentStartDate, WallTime)
    DECODE(recurringPaymentIntervalUnit, ApplePayRecurringPaymentDateUnit)
    DECODE(recurringPaymentIntervalCount, unsigned)
    DECODE(recurringPaymentEndDate, WallTime)
#endif
#if ENABLE(APPLE_PAY_DEFERRED_LINE_ITEM)
    DECODE(deferredPaymentDate, WallTime)
#endif
#if ENABLE(APPLE_PAY_AUTOMATIC_RELOAD_LINE_ITEM)
    DECODE(automaticReloadPaymentThresholdAmount, String)
#endif

#undef DECODE

    return { {
        WTFMove(*type),
        WTFMove(*label),
        WTFMove(*amount),
        WTFMove(*paymentTiming),
#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
        WTFMove(*recurringPaymentStartDate),
        WTFMove(*recurringPaymentIntervalUnit),
        WTFMove(*recurringPaymentIntervalCount),
        WTFMove(*recurringPaymentEndDate),
#endif
#if ENABLE(APPLE_PAY_DEFERRED_LINE_ITEM)
        WTFMove(*deferredPaymentDate),
#endif
#if ENABLE(APPLE_PAY_AUTOMATIC_RELOAD_LINE_ITEM)
        WTFMove(*automaticReloadPaymentThresholdAmount),
#endif
    } };
}

} // namespace WebCore

#endif
