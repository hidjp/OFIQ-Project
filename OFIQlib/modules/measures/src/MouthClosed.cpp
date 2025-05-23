/**
 * @file MouthClosed.cpp
 *
 * @copyright Copyright (c) 2024  Federal Office for Information Security, Germany
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @author OFIQ development team
 */

#include "MouthClosed.h"
#include "FaceMeasures.h"
#include "FaceParts.h"
#include "utils.h"

namespace OFIQ_LIB::modules::measures
{
    static const auto qualityMeasure = OFIQ::QualityMeasure::MouthClosed;

    MouthClosed::MouthClosed(
        const Configuration& configuration)
        : Measure{ configuration, qualityMeasure }
    {
        SigmoidParameters defaultValues;
        defaultValues.setInverse();
        defaultValues.h = 100;
        defaultValues.x0 = 0.2;
        defaultValues.w = 0.06;
        AddSigmoid(qualityMeasure, defaultValues);
    }

    void MouthClosed::Execute(OFIQ_LIB::Session& session)
    {
        auto faceLandmarks = session.getLandmarks();
        auto maxMouthOpening = landmarks::FaceMeasures::GetMaxPairDistance(
            faceLandmarks, landmarks::FaceParts::MOUTH_INNER);

        auto t = tmetric(faceLandmarks);
        
        double rawScore;
        OFIQ::QualityMeasureReturnCode returnCode;
        if (t == 0.0)
        {
            rawScore = std::nan("");
            returnCode = OFIQ::QualityMeasureReturnCode::FailureToAssess;
        }
        else
        {
            rawScore = maxMouthOpening / t;
            returnCode = OFIQ::QualityMeasureReturnCode::Success;
        }

        SetQualityMeasure(session, qualityMeasure, rawScore, returnCode);
    }
}