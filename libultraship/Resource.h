#pragma once

#include <stdint.h>
#include "Utils/BinaryReader.h"
#include "Utils/BinaryWriter.h"
#include "GlobalCtx2.h"
#include "StrHash.h"
#include "File.h"
#include "lib/tinyxml2/tinyxml2.h"

namespace Ship
{
    enum class ResourceType
    {
        Archive          =   0x4F415243,     // OARC
        Model            =   0x4F4D444C,     // OMDL
        Texture          =   0x4F544558,     // OTEX
        Material         =   0x4F4D4154,     // OMAT
        Animation        =   0x4F414E4D,     // OANM
        PlayerAnimation  =   0x4F50414D,     // OPAM
        DisplayList      =   0x4F444C54,     // ODLT
        Room             =   0x4F524F4D,     // OROM
        CollisionHeader  =   0x4F434F4C,     // OCOL
        Skeleton         =   0x4F534B4C,     // OSKL
        SkeletonLimb     =   0x4F534C42,     // OSLB
        Matrix           =   0x4F4D5458,     // OMTX
        Path             =   0x4F505448,     // OPTH
        Vertex           =   0x4F565458,     // OVTX
        Cutscene         =   0x4F435654,     // OCUT
        Array            =   0x4F415252,     // OARR
    };

    enum class DataType
    {
        U8 = 0,
        S8 = 1,
        U16 = 2,
        S16 = 3,
        U32 = 4,
        S32 = 5,
        U64 = 6,
        S64 = 7,
        F16 = 8,
        F32 = 9,
        F64 = 10
    };

    enum class Endianess
    {
        Little = 0,
        Big = 1,
    };
    
    /*
        - Blade Runner:        1982
        - Tron:                1982
        - The Thing:           1982
        - Star Wars ROJ:       1983
        - Predator:            1984
        - Terminator:          1984
        - Mad Max Thunderdome: 1985
        - Back to the Future:  1985
        - Aliens:              1986
        - Star Trek TNG:       1987
        - Robocop:             1987
        - Spaceballs:          1987
        - Terminator 2:        1991
        - Jurassic Park:       1993
        - Demolition Man:      1993
        - Judge Dredd:         1995
        - Star Trek Voyager:   1995
        - The Fifth Element:   1995
        - Waterworld:          1995
        - Stargate:            1997
        - Starship Troopers:   1997
        - Men in Black:        1997
        - Armageddon:          1998
        - Blade:               1998
        - Matrix:              1999
        - Star Wars TPM:       1999
    */

    enum class Version
    {
        // Blade Runner
        Deckard = 0,
        // ...
    };

    class Resource
    {
    public:
        uint64_t id; // Unique Resource ID
        bool isDirty = false;
        void* cachedGameAsset = 0; // Conversion to OoT friendly struct cached...
        std::shared_ptr<File> File;
    };

    class ResourceFile
    {
    public:
        Endianess endianess;    // 0x00 - Endianess of the file
        uint32_t resourceType;  // 0x01 - 4 byte MAGIC
        Version version;     // 0x05 - Based on Ship release numbers
        uint64_t id;            // 0x09 - Unique Resource ID

        virtual void ParseFileBinary(BinaryReader* reader, Resource* res);
        virtual void ParseFileXML(tinyxml2::XMLElement* reader, Resource* res);
        virtual void WriteFileBinary(BinaryWriter* writer, Resource* res);
        virtual void WriteFileXML(tinyxml2::XMLElement* writer, Resource* res);
    };
}