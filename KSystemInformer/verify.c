/*
 * Copyright (c) 2022 Winsider Seminars & Solutions, Inc.  All rights reserved.
 *
 * This file is part of System Informer.
 *
 * Authors:
 *
 *     wj32    2016
 *     jxy-s   2020-2023
 *
 */

#include <kph.h>

#include <trace.h>

#define KPH_KEY_MATERIAL_SIZE        ((ULONG)0x21B)
#define KPH_KEY_ALG_HANDLE           BCRYPT_RSA_ALG_HANDLE
#define KPH_KEY_ALGORITHM            BCRYPT_RSA_ALGORITHM
#define KPH_KEY_HASH_ALGORITHM       BCRYPT_SHA512_ALGORITHM
#define KPH_KEY_HASH_ALGORITHM_BYTES (512 / 8)
#define KPH_KEY_BLOB_PUBLIC          BCRYPT_RSAPUBLIC_BLOB
#define KPH_KEY_PADDING_FLAGS        BCRYPT_PAD_PSS
#define KPH_KEY_PADDING_INFO         (PVOID)&KphpKeyPaddingInfo

#define KPH_VERIFY_SIGNATURE_MAX_LENGTH 1024

typedef enum _KPH_KEY_TYPE
{
    KphKeyTypeTest,
    KphKeyTypeProd,
} KPH_KEY_TYPE, *PKPH_KEY_TYPE;

typedef struct _KPH_KEY
{
    KPH_KEY_TYPE Type;
    BYTE Material[KPH_KEY_MATERIAL_SIZE];
} KPH_KEY, *PKPH_KEY;
typedef const KPH_KEY* PCKPH_KEY;

KPH_PROTECTED_DATA_SECTION_RO_PUSH();
static const KPH_KEY KphpPublicKeys[] =
{
    {
        KphKeyTypeProd, // kph
        {
            0x52, 0x53, 0x41, 0x31, 0x00, 0x10, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
            0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x01, 0xE5, 0xF2, 0xEF, 0xE0, 0xE0, 0x02, 0x05, 0xEA, 0x55,
            0xF8, 0x4C, 0x26, 0xED, 0xF9, 0x55, 0xE3, 0xBD, 0x38, 0x06, 0x5D, 0xF6,
            0x26, 0xA4, 0xFF, 0x69, 0xFC, 0x4D, 0x8C, 0x02, 0x7E, 0x82, 0x96, 0x3D,
            0x90, 0xE8, 0xB7, 0xEB, 0x1A, 0xE3, 0x02, 0x57, 0x0F, 0x1C, 0xE9, 0x93,
            0xD0, 0x61, 0xFC, 0x75, 0xF1, 0xF3, 0xC6, 0x49, 0xF9, 0xBC, 0x39, 0x6F,
            0x80, 0x40, 0xC3, 0xF9, 0xB3, 0xDC, 0xFD, 0x21, 0x28, 0x25, 0x1B, 0x91,
            0x42, 0xB0, 0x29, 0xA4, 0x76, 0x4D, 0x71, 0x4D, 0x38, 0x3C, 0x9F, 0x80,
            0xD9, 0x11, 0xFD, 0xD5, 0x80, 0xB1, 0xFC, 0xB9, 0xC8, 0xCB, 0xE4, 0x6C,
            0x1A, 0x11, 0x8E, 0xE4, 0x9D, 0x3C, 0x24, 0x58, 0x70, 0x64, 0x88, 0x08,
            0x53, 0x7F, 0x8A, 0x30, 0x67, 0x59, 0x91, 0x2E, 0x77, 0xD5, 0x1F, 0x21,
            0x9C, 0x8E, 0x7B, 0x5E, 0xC0, 0x3E, 0x52, 0x26, 0x69, 0x0F, 0x95, 0x14,
            0x72, 0xE5, 0xE9, 0xA2, 0xF7, 0xFC, 0x22, 0x43, 0xB5, 0x1A, 0xB1, 0xDB,
            0x01, 0xC4, 0x6A, 0x13, 0x99, 0xBE, 0x0F, 0x82, 0x59, 0xC8, 0x8F, 0xCA,
            0xF2, 0x86, 0x54, 0x34, 0xF5, 0x4D, 0xD9, 0xD2, 0xA7, 0x4A, 0xDF, 0x94,
            0x9E, 0x13, 0x53, 0xEA, 0xD0, 0x98, 0xB1, 0x15, 0x2D, 0x59, 0xD7, 0xFF,
            0x9B, 0x9C, 0x78, 0x81, 0xDE, 0x90, 0xAF, 0x7E, 0xF4, 0x7D, 0x14, 0xAC,
            0x40, 0x46, 0x13, 0x45, 0x16, 0x0A, 0x22, 0x51, 0xEC, 0x4F, 0x4F, 0xCF,
            0x63, 0x0F, 0x6B, 0xF3, 0xFC, 0x7C, 0x85, 0x1C, 0x1E, 0xBB, 0xF1, 0x80,
            0x34, 0x9F, 0x13, 0x57, 0xB5, 0x02, 0x37, 0xF6, 0xE5, 0x3A, 0x77, 0x90,
            0x1B, 0xB7, 0x6E, 0xA9, 0xA3, 0xF1, 0x33, 0xE2, 0xC7, 0xD8, 0xFF, 0x82,
            0x44, 0x0E, 0x28, 0x30, 0xD6, 0x25, 0x7D, 0x71, 0x4A, 0x68, 0x1C, 0xCD,
            0x70, 0x6F, 0xB0, 0x64, 0x46, 0x0E, 0xE0, 0x1D, 0x30, 0x79, 0xE6, 0x69,
            0x6D, 0x47, 0xF7, 0xEB, 0x09, 0x96, 0x30, 0x40, 0xEF, 0x5C, 0x62, 0xC0,
            0x18, 0x36, 0xA4, 0x95, 0x85, 0x74, 0x91, 0x50, 0xFE, 0x6D, 0xE2, 0xD5,
            0x52, 0xE4, 0x1F, 0x4A, 0x28, 0xB6, 0x9D, 0x5E, 0x34, 0xD5, 0x0C, 0x28,
            0x4D, 0x49, 0xDD, 0x58, 0x40, 0x83, 0x84, 0xA4, 0x0E, 0x1D, 0xE6, 0xF5,
            0xF0, 0x3B, 0x46, 0xAD, 0x2D, 0x64, 0xFA, 0xAC, 0x44, 0x95, 0x52, 0x31,
            0x83, 0x43, 0x67, 0x65, 0x84, 0x74, 0xB3, 0xBD, 0x59, 0x2C, 0x13, 0x8A,
            0x4B, 0xA2, 0xE2, 0x32, 0xF7, 0x42, 0xC6, 0xD6, 0x3D, 0x29, 0x39, 0x1D,
            0x0F, 0xEC, 0x47, 0xA2, 0xBF, 0xED, 0x69, 0x6B, 0xEC, 0x45, 0x04, 0x32,
            0x01, 0x8D, 0x50, 0x48, 0x8B, 0x9C, 0x8E, 0x1E, 0xFA, 0x11, 0x03, 0x87,
            0x47, 0x23, 0x83, 0x98, 0x29, 0x2B, 0xB8, 0x76, 0xD3, 0x64, 0xE7, 0x8C,
            0x22, 0xAE, 0x68, 0xA3, 0xC3, 0x58, 0xC0, 0xA0, 0xFE, 0x37, 0x90, 0x26,
            0x27, 0x78, 0x4E, 0xC3, 0x63, 0x87, 0x3E, 0x20, 0xEF, 0x8A, 0xEA, 0x44,
            0x1E, 0xCC, 0xAD, 0x1F, 0xFC, 0x05, 0x7B, 0x0A, 0x1B, 0x02, 0xFA, 0x1C,
            0xEB, 0x5D, 0x81, 0x6B, 0x09, 0x2B, 0xDE, 0x49, 0x2A, 0xA6, 0xA1, 0x82,
            0xE5, 0x08, 0xBF, 0x40, 0x6E, 0x67, 0x03, 0xAC, 0xB0, 0xDB, 0xB4, 0x9B,
            0x66, 0x38, 0x78, 0x91, 0x79, 0x48, 0x54, 0xCE, 0xC5, 0x32, 0xAE, 0xAB,
            0x35, 0x8B, 0x9C, 0xE9, 0x00, 0x42, 0xBE, 0x98, 0x2C, 0x00, 0x0F, 0x3C,
            0xC7, 0x55, 0xA4, 0x45, 0x98, 0x7C, 0xE2, 0x5E, 0xFF, 0xC0, 0xEC, 0x97,
            0x9C, 0x29, 0x5D, 0x65, 0x00, 0x68, 0x68, 0x97, 0x3B, 0x32, 0x4E, 0x39,
            0x51, 0x95, 0x59, 0xA3, 0x81, 0xE5, 0xDC, 0xF0, 0xAF, 0x77, 0x34, 0x64,
            0x6F, 0xD6, 0x88, 0x03, 0x23, 0xFB, 0x82, 0x62, 0x86, 0xFF, 0x59
        }
    },
    {
        KphKeyTypeTest, // kph-dev
        {
            0x52, 0x53, 0x41, 0x31, 0x00, 0x10, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
            0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x01, 0xAB, 0xDB, 0x39, 0x5E, 0xD1, 0xFA, 0x54, 0x35, 0xD7,
            0x6B, 0x83, 0x62, 0x82, 0x06, 0xC7, 0x20, 0xDB, 0x05, 0x5E, 0x55, 0xF2,
            0x3C, 0x6A, 0x52, 0x1F, 0x0B, 0xC6, 0xC2, 0xB4, 0x83, 0x13, 0xA9, 0xF2,
            0xD6, 0xF7, 0x19, 0x99, 0xB5, 0xB3, 0x52, 0xE7, 0x54, 0x55, 0x17, 0x7F,
            0xE3, 0xA6, 0x6B, 0xD6, 0xB7, 0xDA, 0x38, 0xC8, 0x44, 0xFF, 0x3F, 0x4A,
            0x59, 0x0C, 0x3C, 0x45, 0xA3, 0x35, 0x8B, 0x34, 0x01, 0x82, 0xBD, 0x25,
            0x9B, 0xAF, 0xFC, 0x56, 0x1F, 0x6E, 0xFE, 0xE2, 0xF5, 0xE1, 0x2D, 0xFB,
            0x42, 0x41, 0x46, 0x48, 0x02, 0xEB, 0xEF, 0xEA, 0x41, 0x08, 0x8D, 0x58,
            0xA5, 0x32, 0xFE, 0x8F, 0xE8, 0xBB, 0xF6, 0x36, 0xD9, 0x48, 0xC3, 0x2C,
            0x30, 0x70, 0x57, 0xE0, 0x25, 0x1C, 0xA3, 0xE1, 0x72, 0x76, 0x48, 0xF9,
            0x57, 0x8B, 0x50, 0x67, 0x27, 0x66, 0xD5, 0x70, 0x4F, 0x02, 0x94, 0x9F,
            0xB3, 0xDE, 0x74, 0xF7, 0x7C, 0xD4, 0xEE, 0xFD, 0x95, 0x5D, 0x47, 0xF6,
            0x0A, 0xDE, 0xA1, 0x76, 0x99, 0x52, 0x40, 0x0D, 0xB1, 0x63, 0x1C, 0x65,
            0xA0, 0x04, 0xC8, 0x48, 0xE3, 0xC6, 0x3C, 0x6D, 0x26, 0x10, 0xB9, 0x22,
            0x7D, 0x67, 0x5D, 0x81, 0x44, 0xAF, 0xE0, 0x85, 0xC3, 0xB3, 0x13, 0x27,
            0xB8, 0xA3, 0xC2, 0x28, 0x2A, 0x57, 0xE2, 0xAE, 0x2D, 0xB7, 0x95, 0xC4,
            0x13, 0x65, 0xB9, 0x5C, 0xF5, 0x29, 0x9D, 0x0E, 0x85, 0x37, 0x34, 0x34,
            0xFF, 0x04, 0x17, 0x39, 0x0A, 0x5C, 0x31, 0xD8, 0x59, 0x11, 0xDA, 0x82,
            0x1B, 0x18, 0x0C, 0x8E, 0x24, 0x24, 0x9B, 0x7F, 0x02, 0xB6, 0x5D, 0x31,
            0x6D, 0xB5, 0x15, 0xB6, 0x54, 0x67, 0x1C, 0x6F, 0xF5, 0x2C, 0x42, 0x4B,
            0x7F, 0x6F, 0xAC, 0xD7, 0x56, 0x8A, 0x18, 0xB7, 0x31, 0x02, 0x36, 0xF3,
            0xB6, 0x8B, 0x47, 0x03, 0xFA, 0x84, 0xB5, 0x33, 0x90, 0xD7, 0x33, 0xF8,
            0x32, 0x89, 0x7C, 0x0C, 0x31, 0xB8, 0xA3, 0xF3, 0xAF, 0x46, 0x3F, 0x77,
            0x1A, 0x38, 0x8B, 0x82, 0xBD, 0x4A, 0xAD, 0x93, 0xC6, 0xFC, 0x24, 0x9F,
            0xD4, 0xFF, 0xBB, 0x27, 0xE2, 0x6B, 0x5A, 0x99, 0x5F, 0x70, 0x08, 0xDB,
            0xC9, 0x3A, 0xE8, 0x73, 0x87, 0x63, 0x09, 0x7F, 0x5D, 0x2A, 0x91, 0x24,
            0xFA, 0xEE, 0x9D, 0xC5, 0x81, 0x97, 0x83, 0xC6, 0xD2, 0x6C, 0x5C, 0xFE,
            0x45, 0x5A, 0xA4, 0xA9, 0x9C, 0xEA, 0xEF, 0x98, 0x52, 0xAE, 0x3A, 0xD0,
            0x12, 0x54, 0x75, 0x9E, 0xD0, 0x1E, 0xF7, 0x9D, 0x03, 0x7E, 0xD5, 0x89,
            0x3B, 0xE6, 0x87, 0x75, 0xB3, 0x7B, 0x7C, 0x45, 0x58, 0x1F, 0x8E, 0xE8,
            0x59, 0x78, 0x54, 0xC3, 0xD5, 0x9B, 0x0F, 0xC7, 0x05, 0x34, 0xF2, 0x6C,
            0xCF, 0x19, 0x40, 0x92, 0xDD, 0xF0, 0x1E, 0x5F, 0xA7, 0x04, 0xA2, 0x4D,
            0x2E, 0x7C, 0x57, 0x43, 0x3C, 0xCC, 0xA0, 0x68, 0x0A, 0xEC, 0x47, 0x3D,
            0x27, 0x16, 0x8C, 0x62, 0x33, 0x7F, 0x7D, 0x2D, 0xAA, 0x9D, 0x2F, 0x39,
            0xF7, 0x44, 0xD7, 0x66, 0xE8, 0x1A, 0x38, 0x0C, 0x68, 0x9E, 0x37, 0x3E,
            0x8F, 0xCF, 0x20, 0xBF, 0x9D, 0x3F, 0x4D, 0xA4, 0xFA, 0xFA, 0x67, 0xA8,
            0xAD, 0xB5, 0x04, 0xFF, 0x29, 0x72, 0x4A, 0x87, 0xFD, 0x95, 0xC6, 0x1B,
            0xE2, 0xA7, 0xB3, 0x7F, 0xC7, 0xCB, 0x4A, 0x5A, 0x7A, 0x02, 0x0B, 0x24,
            0xBD, 0x27, 0xC1, 0xED, 0x94, 0x12, 0x5E, 0x7F, 0x45, 0x6E, 0xE5, 0x24,
            0x38, 0x24, 0xA4, 0xF4, 0x93, 0xE6, 0xF6, 0x3F, 0x12, 0xD7, 0x9D, 0x2E,
            0x15, 0xAC, 0x29, 0x2D, 0x83, 0xB2, 0x95, 0x5D, 0x7A, 0x1A, 0xCB, 0x9F,
            0x23, 0xF3, 0x80, 0x3E, 0x8C, 0x72, 0x5F, 0x0F, 0xB2, 0x93, 0x1E, 0x15,
            0xC5, 0xC0, 0x8B, 0xC3, 0xF8, 0x0A, 0xCA, 0x88, 0x07, 0x7F, 0x79
        }
    },
    {
        KphKeyTypeTest, // kph-test
        {
            0x52, 0x53, 0x41, 0x31, 0x00, 0x10, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
            0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x01, 0xC7, 0x95, 0x12, 0x92, 0x18, 0x6F, 0xA2, 0x01, 0x6C,
            0x9A, 0x5F, 0xC1, 0x70, 0x7B, 0xF9, 0xE3, 0x57, 0x75, 0x28, 0x13, 0xC9,
            0xBF, 0xBC, 0x93, 0xCD, 0x55, 0x5C, 0xA9, 0xC2, 0x80, 0x23, 0xA2, 0xEF,
            0xF4, 0xB6, 0x3A, 0xBF, 0x6E, 0x39, 0xC6, 0x23, 0xC1, 0x3B, 0x04, 0xBE,
            0xB5, 0x9B, 0x5C, 0x8A, 0x64, 0xAA, 0x7A, 0x1C, 0x20, 0x7E, 0x2D, 0x52,
            0x55, 0xEC, 0x3E, 0x5C, 0x40, 0xD5, 0x76, 0xC8, 0x2F, 0xFF, 0x14, 0xD7,
            0xA1, 0xE7, 0x1D, 0xF1, 0x3C, 0x73, 0x89, 0x6B, 0xF5, 0xA4, 0xC6, 0x01,
            0x20, 0xB1, 0xD8, 0x21, 0x70, 0xF9, 0x61, 0x76, 0x87, 0x1D, 0x24, 0x0F,
            0x79, 0xEF, 0x5A, 0xE9, 0x91, 0xB0, 0x97, 0x33, 0xB5, 0x6C, 0x9F, 0x91,
            0xED, 0x56, 0x80, 0x6B, 0x40, 0x3C, 0xEF, 0x46, 0xB0, 0xC5, 0xD7, 0xA7,
            0xB5, 0x9D, 0x45, 0x7F, 0x03, 0xEA, 0x70, 0xA1, 0x64, 0xE2, 0x29, 0xB4,
            0x08, 0x69, 0x09, 0xC0, 0xD0, 0x57, 0x38, 0xF7, 0x4B, 0x33, 0x9D, 0xF4,
            0x36, 0x28, 0x15, 0xBF, 0xB1, 0x62, 0x04, 0x10, 0x4D, 0xAB, 0x47, 0x03,
            0x15, 0xAB, 0xC4, 0x78, 0x0E, 0x78, 0x9D, 0x8A, 0x28, 0x74, 0x54, 0xEB,
            0x66, 0xE8, 0x89, 0x45, 0x45, 0x70, 0x2E, 0xB9, 0x03, 0x1C, 0xCB, 0x83,
            0xA0, 0x7C, 0x0B, 0xC5, 0xB2, 0x93, 0x6A, 0x7F, 0x65, 0x4E, 0x35, 0xFB,
            0xF1, 0x58, 0x21, 0xC7, 0x2D, 0x44, 0x53, 0x69, 0x9B, 0x46, 0x23, 0x10,
            0x51, 0xAE, 0x4C, 0x36, 0x18, 0xC4, 0x62, 0xBE, 0x4E, 0x44, 0xFB, 0x98,
            0x42, 0x46, 0x0B, 0x33, 0x48, 0x45, 0x86, 0xEA, 0x7F, 0x75, 0x32, 0xD2,
            0x6B, 0x49, 0x5A, 0x0A, 0x18, 0x37, 0xB1, 0xC3, 0x3E, 0xB0, 0x94, 0xE8,
            0x46, 0x01, 0x07, 0x59, 0x5F, 0xCD, 0xFF, 0x25, 0xE6, 0xB1, 0x23, 0x34,
            0xD5, 0x3A, 0xBA, 0xB9, 0x96, 0xB8, 0xCA, 0xA5, 0x15, 0xD5, 0x07, 0xE3,
            0xE1, 0x63, 0x6F, 0x97, 0x4F, 0x11, 0xA5, 0x49, 0x8E, 0x29, 0x3F, 0xC9,
            0xAF, 0x59, 0x56, 0x4B, 0x11, 0x04, 0x6C, 0xBE, 0x3F, 0xAE, 0x3F, 0x72,
            0xD1, 0x81, 0x15, 0xDE, 0xDB, 0x5B, 0x21, 0xA7, 0x02, 0xE6, 0x50, 0x6D,
            0xB0, 0x9E, 0x98, 0x23, 0x44, 0x9D, 0x1D, 0x21, 0x12, 0x7C, 0x28, 0x1F,
            0x37, 0x6D, 0xCB, 0xCB, 0x1B, 0x01, 0x63, 0xF3, 0xAC, 0xAF, 0x30, 0x41,
            0xBD, 0xA8, 0x39, 0xD7, 0x37, 0x59, 0x56, 0xCC, 0x3B, 0x73, 0x5C, 0xF1,
            0x21, 0x9C, 0xD2, 0x75, 0xEA, 0xE7, 0xBD, 0x82, 0xDF, 0x3D, 0x5A, 0x0E,
            0x9D, 0x7A, 0x41, 0x16, 0x26, 0x72, 0x12, 0xA0, 0x89, 0xFF, 0xAC, 0x83,
            0x87, 0xB5, 0x9F, 0xF0, 0x56, 0xAA, 0x36, 0x9A, 0x1B, 0x41, 0x3C, 0xDF,
            0x75, 0x07, 0x0E, 0xC6, 0xF5, 0xB4, 0x41, 0xF6, 0xCA, 0xB6, 0xE8, 0xF0,
            0x38, 0x98, 0x4C, 0xB1, 0x56, 0xBC, 0xFD, 0xD4, 0xD9, 0xB5, 0x7E, 0x80,
            0x0D, 0xB2, 0xD0, 0x2F, 0x2E, 0x6F, 0x7D, 0xFF, 0xB0, 0xF7, 0x8C, 0xE2,
            0x90, 0xDC, 0x3B, 0x15, 0xF6, 0x07, 0xBC, 0x36, 0x2C, 0x40, 0x93, 0x05,
            0xEF, 0xF3, 0x02, 0xEB, 0x4D, 0xB0, 0xE8, 0xC9, 0x38, 0x4B, 0xBE, 0xA1,
            0xBF, 0xEE, 0x9F, 0x8A, 0x31, 0xE0, 0x76, 0xE1, 0x79, 0x94, 0xB7, 0x4D,
            0x7C, 0xF4, 0x65, 0xF6, 0x8C, 0x35, 0xF5, 0x78, 0x5E, 0xFE, 0x13, 0x72,
            0xC6, 0x13, 0x4C, 0x3A, 0x5E, 0x2C, 0x2B, 0x68, 0x68, 0x59, 0x02, 0x06,
            0xD5, 0x7F, 0x02, 0xA6, 0xF2, 0xB6, 0x16, 0xCA, 0xE8, 0x14, 0x75, 0xDA,
            0x3D, 0xF5, 0x85, 0x3D, 0x6B, 0x2D, 0x03, 0xA4, 0xC1, 0x5F, 0x5D, 0x68,
            0xCC, 0xB1, 0xDE, 0xC1, 0x69, 0x22, 0x99, 0x00, 0x4A, 0x5C, 0x61, 0x14,
            0xAD, 0x50, 0x05, 0xCF, 0x6E, 0xEE, 0x4C, 0xC9, 0x58, 0xA4, 0xE5
        }
    }
};
static const BCRYPT_PSS_PADDING_INFO KphpKeyPaddingInfo =
{
    KPH_KEY_HASH_ALGORITHM,
    KPH_KEY_HASH_ALGORITHM_BYTES
};
static const UNICODE_STRING KphpSigExtension = RTL_CONSTANT_STRING(L".sig");
KPH_PROTECTED_DATA_SECTION_RO_POP();
KPH_PROTECTED_DATA_SECTION_PUSH();
static BCRYPT_KEY_HANDLE KphpPublicKeyHandles[ARRAYSIZE(KphpPublicKeys)] = { 0 };
static ULONG KphpPublicKeyHandlesCount = 0;
C_ASSERT(ARRAYSIZE(KphpPublicKeyHandles) == ARRAYSIZE(KphpPublicKeys));
KPH_PROTECTED_DATA_SECTION_POP();

PAGED_FILE();

/**
 * \brief Verifies that the specified signature matches the specified hash by
 * using one of the known public keys.
 *
 * \param[in] KeyHandle The key handle to use for verification, if NULL the
 * pinned keys are used to verify the signature.
 * \param[in] Hash The hash to verify.
 * \param[in] Signature The signature to check.
 * \param[in] SignatureLength The length of the signature.
 *
 * \return Successful or errant status.
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphpVerifyHash(
    _In_opt_ BCRYPT_KEY_HANDLE KeyHandle,
    _In_ PKPH_HASH_INFORMATION HashInformation,
    _In_ PBYTE Signature,
    _In_ ULONG SignatureLength
    )
{
    NTSTATUS status;

    PAGED_CODE_PASSIVE();

    status = STATUS_UNSUCCESSFUL;

    if (KeyHandle)
    {
        status = BCryptVerifySignature(KeyHandle,
                                       KPH_KEY_PADDING_INFO,
                                       HashInformation->Hash,
                                       HashInformation->Length,
                                       Signature,
                                       SignatureLength,
                                       KPH_KEY_PADDING_FLAGS);
    }
    else
    {
        for (ULONG i = 0; i < KphpPublicKeyHandlesCount; i++)
        {
            status = BCryptVerifySignature(KphpPublicKeyHandles[i],
                                           KPH_KEY_PADDING_INFO,
                                           HashInformation->Hash,
                                           HashInformation->Length,
                                           Signature,
                                           SignatureLength,
                                           KPH_KEY_PADDING_FLAGS);
            if (NT_SUCCESS(status))
            {
                return status;
            }
        }
    }

    return status;
}

/**
 * \brief Closes a verification key handle.
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID KphVerifyCloseKey(
    _In_ BCRYPT_KEY_HANDLE KeyHandle
    )
{
    PAGED_CODE_PASSIVE();

    BCryptDestroyKey(KeyHandle);
}

/**
 * \brief Creates a verification key handle.
 *
 * \param[out] KeyHandle The created key handle.
 * \param[in] KeyMaterial The key material to use.
 * \param[in] KeyMaterialLength The length of the key material.
 *
 * \return Successful or errant status.
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphVerifyCreateKey(
    _Out_ BCRYPT_KEY_HANDLE* KeyHandle,
    _In_ PBYTE KeyMaterial,
    _In_ ULONG KeyMaterialLength
    )
{
    NTSTATUS status;

    PAGED_CODE_PASSIVE();

    status = BCryptImportKeyPair(KPH_KEY_ALG_HANDLE,
                                 NULL,
                                 KPH_KEY_BLOB_PUBLIC,
                                 KeyHandle,
                                 (PUCHAR)KeyMaterial,
                                 KeyMaterialLength,
                                 0);
    if (!NT_SUCCESS(status))
    {
        *KeyHandle = NULL;
    }

    return status;
}

/**
 * \brief Verifies a buffer matches the provided signature.
 *
 * \param[in] KeyHandle The key handle to use for verification, if NULL the
 * pinned keys are used to verify the signature.
 * \param[in] Buffer The buffer to verify.
 * \param[in] BufferLength The length of the buffer.
 * \param[in] Signature The signature to check.
 * \param[in] SignatureLength The length of the signature.
 *
 * \return Successful or errant status.
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphVerifyBufferEx(
    _In_opt_ BCRYPT_KEY_HANDLE KeyHandle,
    _In_ PBYTE Buffer,
    _In_ ULONG BufferLength,
    _In_ PBYTE Signature,
    _In_ ULONG SignatureLength
    )
{
    NTSTATUS status;
    KPH_HASH_INFORMATION hashInfo;

    PAGED_CODE_PASSIVE();

    status = KphHashBuffer(Buffer,
                           BufferLength,
                           KphHashAlgorithmSha512,
                           &hashInfo);
    if (!NT_SUCCESS(status))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "KphHashBuffer failed: %!STATUS!",
                      status);

        return status;
    }

    status = KphpVerifyHash(KeyHandle, &hashInfo, Signature, SignatureLength);
    if (!NT_SUCCESS(status))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "KphpVerifyHash failed: %!STATUS!",
                      status);

        return status;
    }

    return STATUS_SUCCESS;
}

/**
 * \brief Verifies a buffer matches the provided signature.
 *
 * \param[in] Buffer The buffer to verify.
 * \param[in] BufferLength The length of the buffer.
 * \param[in] Signature The signature to check.
 * \param[in] SignatureLength The length of the signature.
 *
 * \return Successful or errant status.
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphVerifyBuffer(
    _In_ PBYTE Buffer,
    _In_ ULONG BufferLength,
    _In_ PBYTE Signature,
    _In_ ULONG SignatureLength
    )
{
    PAGED_CODE_PASSIVE();

    return KphVerifyBufferEx(NULL,
                             Buffer,
                             BufferLength,
                             Signature,
                             SignatureLength);
}

#define KphpVerifyValidFileName(FileName)                                      \
    (((FileName)->Length > KphpSigExtension.Length) &&                         \
     ((FileName)->Buffer[0] == L'\\'))

/**
 * \brief Verifies a file object.
 *
 * \param[in] FileObject File object to verify.
 * \param[in] FileName Optional file name to use for verification, if not
 * provided the file name is looked up from the file object.
 *
 * \return Successful or errant status.
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphVerifyFileObject(
    _In_ PFILE_OBJECT FileObject,
    _In_opt_ PCUNICODE_STRING FileName
    )
{
    NTSTATUS status;
    PCUNICODE_STRING fileName;
    PUNICODE_STRING localFileName;
    UNICODE_STRING signatureFileName;
    OBJECT_ATTRIBUTES objectAttributes;
    HANDLE signatureFileHandle;
    IO_STATUS_BLOCK ioStatusBlock;
    PBYTE signature;
    ULONG signatureLength;
    KPH_HASH_INFORMATION hashInfo;

    PAGED_CODE_PASSIVE();

    localFileName = NULL;
    RtlZeroMemory(&signatureFileName, sizeof(signatureFileName));
    signatureFileHandle = NULL;
    signature = NULL;

    if (FileName)
    {
        fileName = FileName;
    }
    else
    {
        status = KphGetNameFileObject(FileObject, &localFileName);
        if (!NT_SUCCESS(status))
        {
            KphTracePrint(TRACE_LEVEL_VERBOSE,
                          VERIFY,
                          "KphGetNameFileObject failed: %!STATUS!",
                          status);

            goto Exit;
        }

        fileName = localFileName;
    }

    if (!KphpVerifyValidFileName(fileName))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "File name is invalid \"%wZ\"",
                      fileName);

        status = STATUS_OBJECT_NAME_INVALID;
        goto Exit;
    }

    status = RtlDuplicateUnicodeString(0, fileName, &signatureFileName);
    if (!NT_SUCCESS(status))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "RtlDuplicateUnicodeString failed: %!STATUS!",
                      status);

        RtlZeroMemory(&signatureFileName, sizeof(signatureFileName));
        goto Exit;
    }

    //
    // Replace the file extension with ".sig". Our verification requires that
    // the signature file be placed alongside the file we're verifying.
    //
    if (signatureFileName.Length < KphpSigExtension.Length)
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "Signature file name length invalid \"%wZ\"",
                      &signatureFileName);

        status = STATUS_OBJECT_NAME_INVALID;
        goto Exit;
    }

    signatureFileName.Length -= KphpSigExtension.Length;

    status = RtlAppendUnicodeStringToString(&signatureFileName,
                                            &KphpSigExtension);
    if (!NT_SUCCESS(status))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "RtlAppendUnicodeStringToString failed: %!STATUS!",
                      status);

        goto Exit;
    }

    InitializeObjectAttributes(&objectAttributes,
                               &signatureFileName,
                               OBJ_KERNEL_HANDLE | OBJ_DONT_REPARSE,
                               NULL,
                               NULL);

    status = KphCreateFile(&signatureFileHandle,
                           FILE_READ_ACCESS | SYNCHRONIZE,
                           &objectAttributes,
                           &ioStatusBlock,
                           NULL,
                           FILE_ATTRIBUTE_NORMAL,
                           FILE_SHARE_READ,
                           FILE_OPEN,
                           (FILE_NON_DIRECTORY_FILE |
                            FILE_SYNCHRONOUS_IO_NONALERT |
                            FILE_COMPLETE_IF_OPLOCKED),
                           NULL,
                           0,
                           IO_IGNORE_SHARE_ACCESS_CHECK,
                           KernelMode);
    if (!NT_SUCCESS(status))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "Failed to open signature file \"%wZ\": %!STATUS!",
                      &signatureFileName,
                      status);

        signatureFileHandle = NULL;
        goto Exit;
    }
    else if (status == STATUS_OPLOCK_BREAK_IN_PROGRESS)
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "Failed to open signature file \"%wZ\": %!STATUS!",
                      &signatureFileName,
                      status);

        status = STATUS_SHARING_VIOLATION;
        goto Exit;
    }

    signature = KphAllocatePaged(KPH_VERIFY_SIGNATURE_MAX_LENGTH,
                                 KPH_TAG_VERIFY_SIGNATURE);
    if (!signature)
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "Failed to allocate signature buffer");

        status = STATUS_INSUFFICIENT_RESOURCES;
        goto Exit;
    }

    status = ZwReadFile(signatureFileHandle,
                        NULL,
                        NULL,
                        NULL,
                        &ioStatusBlock,
                        signature,
                        KPH_VERIFY_SIGNATURE_MAX_LENGTH,
                        NULL,
                        NULL);
    if (!NT_SUCCESS(status))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "Failed to read signature file \"%wZ\": %!STATUS!",
                      &signatureFileName,
                      status);

        goto Exit;
    }

    signatureLength = (ULONG)ioStatusBlock.Information;

    hashInfo.Algorithm = KphHashAlgorithmSha512;

    status = KphQueryHashInformationFileObject(FileObject,
                                               &hashInfo,
                                               sizeof(hashInfo));
    if (!NT_SUCCESS(status))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "KphQueryHashInformationFileObject failed: %!STATUS!",
                      status);

        goto Exit;
    }

    status = KphpVerifyHash(NULL, &hashInfo, signature, signatureLength);
    if (!NT_SUCCESS(status))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "KphpVerifyHash failed: %!STATUS!",
                      status);

        goto Exit;
    }

    status = STATUS_SUCCESS;

Exit:

    if (signature)
    {
        KphFree(signature, KPH_TAG_VERIFY_SIGNATURE);
    }

    if (signatureFileHandle)
    {
        ObCloseHandle(signatureFileHandle, KernelMode);
    }

    RtlFreeUnicodeString(&signatureFileName);

    if (localFileName)
    {
        KphFreeNameFileObject(localFileName);
    }

    return status;
}

/**
 * \brief Verifies a file by name.
 *
 * \param[in] FileName File name to verify.
 * \param[in] FileObject Optional file object to use for verification. If
 * provided the opened file object is checked to match. This is useful when the
 * file object is known but not in a state where you can use it directly.
 *
 * \return Successful or errant status.
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphVerifyFile(
    _In_ PCUNICODE_STRING FileName,
    _In_opt_ PFILE_OBJECT FileObject
    )
{
    NTSTATUS status;
    OBJECT_ATTRIBUTES objectAttributes;
    IO_STATUS_BLOCK ioStatusBlock;
    HANDLE fileHandle;
    PFILE_OBJECT fileObject;

    PAGED_CODE_PASSIVE();

    fileObject = NULL;
    fileHandle = NULL;

    if (!KphpVerifyValidFileName(FileName))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "File name is invalid \"%wZ\"",
                      FileName);

        status = STATUS_OBJECT_NAME_INVALID;
        goto Exit;
    }

    InitializeObjectAttributes(&objectAttributes,
                               (PUNICODE_STRING)FileName,
                               OBJ_KERNEL_HANDLE | OBJ_DONT_REPARSE,
                               NULL,
                               NULL);

    status = KphCreateFile(&fileHandle,
                           FILE_READ_ACCESS | SYNCHRONIZE,
                           &objectAttributes,
                           &ioStatusBlock,
                           NULL,
                           FILE_ATTRIBUTE_NORMAL,
                           FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                           FILE_OPEN,
                           (FILE_NON_DIRECTORY_FILE |
                            FILE_SYNCHRONOUS_IO_NONALERT |
                            FILE_COMPLETE_IF_OPLOCKED),
                           NULL,
                           0,
                           IO_IGNORE_SHARE_ACCESS_CHECK,
                           KernelMode);
    if (!NT_SUCCESS(status))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      HASH,
                      "KphCreateFile failed: %!STATUS!",
                      status);

        fileHandle = NULL;
        goto Exit;
    }
    else if (status == STATUS_OPLOCK_BREAK_IN_PROGRESS)
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      HASH,
                      "KphCreateFile failed: %!STATUS!",
                      status);

        status = STATUS_SHARING_VIOLATION;
        goto Exit;
    }

    status = ObReferenceObjectByHandle(fileHandle,
                                       0,
                                       *IoFileObjectType,
                                       KernelMode,
                                       &fileObject,
                                       NULL);
    if (!NT_SUCCESS(status))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "ObReferenceObjectByHandle failed: %!STATUS!",
                      status);

        fileObject = NULL;
        goto Exit;
    }

    if (FileObject && !KphIsSameFile(FileObject, fileObject))
    {
        KphTracePrint(TRACE_LEVEL_VERBOSE,
                      VERIFY,
                      "File objects do not match!");

        status = STATUS_INVALID_PARAMETER;
        goto Exit;
    }

    status = KphVerifyFileObject(fileObject, FileName);

Exit:

    if (fileObject)
    {
        ObDereferenceObject(fileObject);
    }

    if (fileHandle)
    {
        ObCloseHandle(fileHandle, KernelMode);
    }

    return status;
}

/**
 * \brief Initializes verification infrastructure.
 *
 * \return Successful or errant status.
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphInitializeVerify(
    VOID
    )
{
    BOOLEAN testSigning;

    PAGED_CODE_PASSIVE();

    testSigning = KphTestSigningEnabled();

    for (ULONG i = 0; i < ARRAYSIZE(KphpPublicKeys); i++)
    {
        NTSTATUS status;
        PCKPH_KEY key;
        BCRYPT_KEY_HANDLE keyHandle;

        key = &KphpPublicKeys[i];

        if (!testSigning && (key->Type == KphKeyTypeTest))
        {
            continue;
        }

        status = KphVerifyCreateKey(&keyHandle,
                                    (PBYTE)key->Material,
                                    KPH_KEY_MATERIAL_SIZE);
        if (!NT_SUCCESS(status))
        {
            KphTracePrint(TRACE_LEVEL_VERBOSE,
                          VERIFY,
                          "KphVerifyCreateKey failed: %!STATUS!",
                          status);

            return status;
        }

        KphpPublicKeyHandles[KphpPublicKeyHandlesCount++] = keyHandle;
    }

    return STATUS_SUCCESS;
}

/**
 * \brief Cleans up verification infrastructure.
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID KphCleanupVerify(
    VOID
    )
{
    PAGED_CODE_PASSIVE();

    for (ULONG i = 0; i < KphpPublicKeyHandlesCount; i++)
    {
        KphVerifyCloseKey(KphpPublicKeyHandles[i]);
    }
}
