/* License: Apache 2.0. See LICENSE file in root directory.
   Copyright(c) 2017 Intel Corporation. All Rights Reserved. */

#ifndef R4XX_ADVANCED_MODE_HPP
#define R4XX_ADVANCED_MODE_HPP

#include <librealsense/rs2.hpp>
#include <librealsense/rs2_advanced_mode.h>

inline std::ostream & operator << (std::ostream & o, rs2_rs400_visual_preset preset) { return o << rs2_advanced_mode_preset_to_string(preset); }

bool operator==(const STDepthControlGroup& a, const STDepthControlGroup& b)
{
    return (a.plusIncrement              == b.plusIncrement &&
            a.minusDecrement             == b.minusDecrement &&
            a.deepSeaMedianThreshold     == b.deepSeaMedianThreshold &&
            a.scoreThreshA               == b.scoreThreshA &&
            a.scoreThreshB               == b.scoreThreshB &&
            a.textureDifferenceThreshold == b.textureDifferenceThreshold &&
            a.textureCountThreshold      == b.textureCountThreshold &&
            a.deepSeaSecondPeakThreshold == b.deepSeaSecondPeakThreshold &&
            a.deepSeaNeighborThreshold   == b.deepSeaNeighborThreshold &&
            a.lrAgreeThreshold           == b.lrAgreeThreshold);
}

bool operator==(const STRsm& a, const STRsm& b)
{
    return (a.rsmBypass        == b.rsmBypass        &&
            a.diffThresh       == b.diffThresh       &&
            a.sloRauDiffThresh == b.sloRauDiffThresh &&
            a.removeThresh     == b.removeThresh);
}

bool operator==(const STRauSupportVectorControl& a, const STRauSupportVectorControl& b)
{
    return (a.minWest  == b.minWest  &&
            a.minEast  == b.minEast  &&
            a.minWEsum == b.minWEsum &&
            a.minNorth == b.minNorth &&
            a.minSouth == b.minSouth &&
            a.minNSsum == b.minNSsum &&
            a.uShrink  == b.uShrink  &&
            a.vShrink  == b.vShrink);
}

bool operator==(const STColorControl& a, const STColorControl& b)
{
    return (a.disableSADColor      == b.disableSADColor      &&
            a.disableRAUColor      == b.disableRAUColor      &&
            a.disableSLORightColor == b.disableSLORightColor &&
            a.disableSLOLeftColor  == b.disableSLOLeftColor  &&
            a.disableSADNormalize  == b.disableSADNormalize);
}

bool operator==(const STRauColorThresholdsControl& a, const STRauColorThresholdsControl& b)
{
    return (a.rauDiffThresholdRed   == b.rauDiffThresholdRed   &&
            a.rauDiffThresholdGreen == b.rauDiffThresholdGreen &&
            a.rauDiffThresholdBlue  == b.rauDiffThresholdBlue);
}

bool operator==(const STSloColorThresholdsControl& a, const STSloColorThresholdsControl& b)
{
    return (a.diffThresholdRed   == b.diffThresholdRed   &&
            a.diffThresholdGreen == b.diffThresholdGreen &&
            a.diffThresholdBlue  == b.diffThresholdBlue);
}

bool operator==(const STSloPenaltyControl& a, const STSloPenaltyControl& b)
{
    return (a.sloK1Penalty     == b.sloK1Penalty     &&
            a.sloK2Penalty     == b.sloK2Penalty     &&
            a.sloK1PenaltyMod1 == b.sloK1PenaltyMod1 &&
            a.sloK2PenaltyMod1 == b.sloK2PenaltyMod1 &&
            a.sloK1PenaltyMod2 == b.sloK1PenaltyMod2 &&
            a.sloK2PenaltyMod2 == b.sloK2PenaltyMod2);
}

bool operator==(const STHdad& a, const STHdad& b)
{
    return (a.lambdaCensus == b.lambdaCensus &&
            a.lambdaAD     == b.lambdaAD     &&
            a.ignoreSAD    == b.ignoreSAD);
}

bool operator==(const STColorCorrection& a, const STColorCorrection& b)
{
    return (a.colorCorrection1  == b.colorCorrection1  &&
            a.colorCorrection2  == b.colorCorrection2  &&
            a.colorCorrection3  == b.colorCorrection3  &&
            a.colorCorrection4  == b.colorCorrection4  &&
            a.colorCorrection5  == b.colorCorrection5  &&
            a.colorCorrection6  == b.colorCorrection6  &&
            a.colorCorrection7  == b.colorCorrection7  &&
            a.colorCorrection8  == b.colorCorrection8  &&
            a.colorCorrection9  == b.colorCorrection9  &&
            a.colorCorrection10 == b.colorCorrection10 &&
            a.colorCorrection11 == b.colorCorrection11 &&
            a.colorCorrection12 == b.colorCorrection12);
}

bool operator==(const STAEControl& a, const STAEControl& b)
{
    return (a.meanIntensitySetPoint == b.meanIntensitySetPoint);
}

bool operator==(const STDepthTableControl& a, const STDepthTableControl& b)
{
    return (a.depthUnits     == b.depthUnits     &&
            a.depthClampMin  == b.depthClampMin  &&
            a.depthClampMax  == b.depthClampMax  &&
            a.disparityMode  == b.disparityMode  &&
            a.disparityShift == b.disparityShift);
}

bool operator==(const STCensusRadius& a, const STCensusRadius& b)
{
    return (a.uDiameter == b.uDiameter &&
            a.vDiameter == b.vDiameter);
}

namespace rs400
{
    class advanced_mode : public rs2::device
    {
    public:
        advanced_mode(rs2::device d)
                : rs2::device(d.get())
        {
            rs2_error* e = nullptr;
            if(rs2_is_device_extendable_to(_dev.get(), RS2_EXTENSION_TYPE_ADVANCED_MODE, &e) == 0 && !e)
            {
                _dev = nullptr;
            }
            rs2::error::handle(e);
        }

        void toggle_advanced_mode(bool enable)
        {
            rs2_error* e = nullptr;
            rs2_toggle_advanced_mode(_dev.get(), enable, &e);
            rs2::error::handle(e);
        }

        bool is_enabled() const
        {
            rs2_error* e = nullptr;
            int enabled;
            rs2_is_enabled(_dev.get(), &enabled, &e);
            rs2::error::handle(e);

            return enabled;
        }

        void set_depth_control(STDepthControlGroup& group)
        {
            rs2_error* e = nullptr;
            rs2_set_depth_control(_dev.get(), &group, &e);
            rs2::error::handle(e);
        }

        STDepthControlGroup get_depth_control(int mode = 0) const
        {
            rs2_error* e = nullptr;
            STDepthControlGroup group{};
            rs2_get_depth_control(_dev.get(), &group, mode, &e);
            rs2::error::handle(e);

            return group;
        }

        void set_rsm(STRsm& group)
        {
            rs2_error* e = nullptr;
            rs2_set_rsm(_dev.get(), &group, &e);
            rs2::error::handle(e);
        }

        STRsm get_rsm(int mode = 0) const
        {
            rs2_error* e = nullptr;
            STRsm group{};
            rs2_get_rsm(_dev.get(), &group, mode, &e);
            rs2::error::handle(e);

            return group;
        }

        void set_rau_support_vector_control(STRauSupportVectorControl& group)
        {
            rs2_error* e = nullptr;
            rs2_set_rau_support_vector_control(_dev.get(), &group, &e);
            rs2::error::handle(e);
        }

        STRauSupportVectorControl get_rau_support_vector_control(int mode = 0) const
        {
            rs2_error* e = nullptr;
            STRauSupportVectorControl group{};
            rs2_get_rau_support_vector_control(_dev.get(), &group, mode, &e);
            rs2::error::handle(e);

            return group;
        }

        void set_color_control(STColorControl& group)
        {
            rs2_error* e = nullptr;
            rs2_set_color_control(_dev.get(),  &group, &e);
            rs2::error::handle(e);
        }

        STColorControl get_color_control(int mode = 0) const
        {
            rs2_error* e = nullptr;
            STColorControl group{};
            rs2_get_color_control(_dev.get(), &group, mode, &e);
            rs2::error::handle(e);

            return group;
        }

        void set_rau_thresholds_control(STRauColorThresholdsControl& group)
        {
            rs2_error* e = nullptr;
            rs2_set_rau_thresholds_control(_dev.get(), &group, &e);
            rs2::error::handle(e);
        }

        STRauColorThresholdsControl get_rau_thresholds_control(int mode = 0) const
        {
            rs2_error* e = nullptr;
            STRauColorThresholdsControl group{};
            rs2_get_rau_thresholds_control(_dev.get(), &group, mode, &e);
            rs2::error::handle(e);

            return group;
        }

        void set_slo_color_thresholds_control(STSloColorThresholdsControl& group)
        {
            rs2_error* e = nullptr;
            rs2_set_slo_color_thresholds_control(_dev.get(), &group, &e);
            rs2::error::handle(e);
        }

        STSloColorThresholdsControl get_slo_color_thresholds_control(int mode = 0) const
        {
            rs2_error* e = nullptr;
            STSloColorThresholdsControl group{};
            rs2_get_slo_color_thresholds_control(_dev.get(), &group, mode, &e);
            rs2::error::handle(e);

            return group;
        }

        void set_slo_penalty_control(STSloPenaltyControl& group)
        {
            rs2_error* e = nullptr;
            rs2_set_slo_penalty_control(_dev.get(), &group, &e);
            rs2::error::handle(e);
        }

        STSloPenaltyControl get_slo_penalty_control(int mode = 0) const
        {
            rs2_error* e = nullptr;
            STSloPenaltyControl group{};
            rs2_get_slo_penalty_control(_dev.get(), &group, mode, &e);
            rs2::error::handle(e);

            return group;
        }

        void set_hdad(STHdad& group)
        {
            rs2_error* e = nullptr;
            rs2_set_hdad(_dev.get(), &group, &e);
            rs2::error::handle(e);
        }

        STHdad get_hdad(int mode = 0) const
        {
            rs2_error* e = nullptr;
            STHdad group{};
            rs2_get_hdad(_dev.get(), &group, mode, &e);
            rs2::error::handle(e);

            return group;
        }

        void set_color_correction(STColorCorrection& group)
        {
            rs2_error* e = nullptr;
            rs2_set_color_correction(_dev.get(), &group, &e);
            rs2::error::handle(e);
        }

        STColorCorrection get_color_correction(int mode = 0) const
        {
            rs2_error* e = nullptr;
            STColorCorrection group{};
            rs2_get_color_correction(_dev.get(), &group, mode, &e);
            rs2::error::handle(e);

            return group;
        }

        void set_depth_table(STDepthTableControl& group)
        {
            rs2_error* e = nullptr;
            rs2_set_depth_table(_dev.get(), &group, &e);
            rs2::error::handle(e);
        }

        STDepthTableControl get_depth_table(int mode = 0) const
        {
            rs2_error* e = nullptr;
            STDepthTableControl group{};
            rs2_get_depth_table(_dev.get(), &group, mode, &e);
            rs2::error::handle(e);

            return group;
        }

        void set_ae_control(STAEControl& group)
        {
            rs2_error* e = nullptr;
            rs2_set_ae_control(_dev.get(), &group, &e);
            rs2::error::handle(e);
        }

        STAEControl get_ae_control(int mode = 0) const
        {
            rs2_error* e = nullptr;
            STAEControl group{};
            rs2_get_ae_control(_dev.get(), &group, mode, &e);
            rs2::error::handle(e);

            return group;
        }

        void set_census(STCensusRadius& group)
        {
            rs2_error* e = nullptr;
            rs2_set_census(_dev.get(), &group, &e);
            rs2::error::handle(e);
        }

        STCensusRadius get_census(int mode = 0) const
        {
            rs2_error* e = nullptr;
            STCensusRadius group{};
            rs2_get_census(_dev.get(), &group, mode, &e);
            rs2::error::handle(e);

            return group;
        }

        std::string generate_json_data() const
        {
            std::string results;

            rs2_error* e = nullptr;
            std::shared_ptr<rs2_json_data> json_data(
                    rs2_generate_json_data(_dev.get(), &e),
                    rs2_delete_json_data);
            rs2::error::handle(e);

            auto size = rs2_get_json_content_size(json_data.get(), &e);
            rs2::error::handle(e);

            auto start = rs2_get_json_content(json_data.get(), &e);
            rs2::error::handle(e);

            results.insert(results.begin(), start, start + size);

            return results;
        }

        void apply_controls_from_json_content(const std::string& json_content)
        {
            rs2_error* e = nullptr;
            rs2_apply_controls_from_json_content(_dev.get(),
                                                 json_content.data(),
                                                 json_content.size(),
                                                 &e);
            rs2::error::handle(e);
        }
    };
}
#endif // R4XX_ADVANCED_MODE_HPP
