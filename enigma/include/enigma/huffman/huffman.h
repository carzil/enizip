#pragma once

#include <cstdint>
#include <ostream>
#include <memory>
#include <vector>

#include "enigma/common/codec.h"
#include "enigma/common/codeword.h"
#include "enigma/huffman/tree.h"
#include "enigma/huffman/prefix_table.h"
#include "enigma_export.h"

namespace Codecs {

class ENIGMA_API HuffmanCodec : public CodecIFace {
    private:
        HuffmanTree* tree;
        size_t frequencies[258];
        Codeword* char_table[258]; // here we use two jumps in memory, needs to optimize
        PrefixTable* prefix_table;

        void GenerateCodes();

    public:
        HuffmanCodec();
        ~HuffmanCodec();

        virtual size_t encode(const string_view&, char*) override;
        virtual size_t decode(const string_view&, char*) override;

        virtual string save() const override;
        virtual void load(const string_view&) override;

        virtual size_t sample_size(size_t records_total) const override;
        virtual void Learn(const vector<string>& samples) override;
        virtual void Learn(const string& samples) override;
        virtual void EndLearning() override;

        virtual void reset() override;
};
}
