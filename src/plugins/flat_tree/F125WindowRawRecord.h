
#pragma once

#include <cstdint>
#include <vector>
#include <TTree.h>
#include "AlignedArraysIO.h"

namespace flatio {
    struct F125WindowRawRecord
    {
        uint32_t roc;
        uint32_t slot;
        uint32_t channel;
        bool invalid_samples;
        bool overflow;
        uint32_t itrigger;
        std::vector<uint16_t> samples;
    };
    
    class F125WindowRawRecordIO: public AlignedArraysIO
    {
    public:
        void bindToTree(TTree *tree) override {
            m_is_bound = true;
            tree->Branch("f125_wraw_count", &m_count, "f125_wraw_count/l");
            tree->Branch("f125_wraw_roc", &m_vect_roc);
            tree->Branch("f125_wraw_slot", &m_vect_slot);
            tree->Branch("f125_wraw_channel", &m_vect_channel);
            tree->Branch("f125_wraw_invalid_samples", &m_vect_invalid_samples);
            tree->Branch("f125_wraw_overflow", &m_vect_overflow);
            tree->Branch("f125_wraw_itrigger", &m_vect_itrigger);
            tree->Branch("f125_wraw_samples", &m_vect_samples);
        }

        void clear() override {
            m_count = 0;
            m_vect_roc.clear();
            m_vect_slot.clear();
            m_vect_channel.clear();
            m_vect_invalid_samples.clear();
            m_vect_overflow.clear();
            m_vect_itrigger.clear();
            m_vect_samples.clear();
        }
        
        void add(const F125WindowRawRecord& data) {
            if(!m_is_bound) {
                throw std::logic_error("Can't add F125WindowRawRecord data because F125WindowRawRecordIO is not bound to tree");
            }
            m_count++;
            m_vect_roc.push_back(data.roc);
            m_vect_slot.push_back(data.slot);
            m_vect_channel.push_back(data.channel);
            m_vect_invalid_samples.push_back(data.invalid_samples);
            m_vect_overflow.push_back(data.overflow);
            m_vect_itrigger.push_back(data.itrigger);
            m_vect_samples.push_back(data.samples);
        }
        
        bool isBoundToTree() const { return m_is_bound; }
        
    private:
        bool m_is_bound = false;
        uint64_t m_count;
        std::vector<uint32_t> m_vect_roc;
        std::vector<uint32_t> m_vect_slot;
        std::vector<uint32_t> m_vect_channel;
        std::vector<bool> m_vect_invalid_samples;
        std::vector<bool> m_vect_overflow;
        std::vector<uint32_t> m_vect_itrigger;
        std::vector<std::vector<uint16_t>> m_vect_samples;
    };
}
