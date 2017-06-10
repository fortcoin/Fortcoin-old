// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Fortcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (  0, uint256("0x"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1493911768, // * UNIX timestamp of last checkpoint block
        1998064,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        2800        // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0x0"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1405699509,
        201,
        500
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0x0"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
     	pchMessageStart[0] = 0xbd;
        pchMessageStart[1] = 0xa3;
        pchMessageStart[2] = 0xc8;
        pchMessageStart[3] = 0xb1;
        vAlertPubKey = ParseHex("04201ba1cad0cf49ed56dbd95ec22e5ff392a756a0e6e69d9f455cb9ebabbd96cc287ad65df52bdd84e25cac8ea6b08770c7e332dfc2a218f111ac884b0d6449be");
        nDefaultPort = 49999;
        bnProofOfWorkLimit = ~uint256(0) >> 20;  // Fortcoin starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // Fortcoin: 1 day
        nTargetSpacing = 60; // Fortcoin: 1 minutes

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         * 
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "The movie Wargames is released";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04201ba1cad0cf49ed56dbd95ec22e5ff392a756a0e6e69d9f455cb9ebabbd96cc287ad65df52bdd84e25cac8ea6b08770c7e332dfc2a218f111ac884b0d6449be") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1496558297;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 56172;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000004c0077ae1e33fc103a38fc8c42c27ecfb7db7fb7f7531a9b0248852ef76"));
        assert(genesis.hashMerkleRoot == uint256("0x3c35ff11d12cce416b04526ceac7880dfc622ca96dbdb161ef53a6dbd5896e3b"));

	vSeeds.push_back(CDNSSeedData("fortcoin seeds","seed.fortcoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,35);
        // Fortcoin script addresses start with '7'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,10);
        // Fortcoin private keys start with '7' or 'X'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,163);
        // Fortcoin BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Fortcoin BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Fortcoin BIP44 coin type is '5'
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04201ba1cad0cf49ed56dbd95ec22e5ff392a756a0e6e69d9f455cb9ebabbd96cc287ad65df52bdd84e25cac8ea6b08770c7e332dfc2a218f111ac884b0d6449be";
        strMasternodePaymentsPubKey = "04201ba1cad0cf49ed56dbd95ec22e5ff392a756a0e6e69d9f455cb9ebabbd96cc287ad65df52bdd84e25cac8ea6b08770c7e332dfc2a218f111ac884b0d6449be";
        strDarksendPoolDummyAddress = "Xq19GqFvajRrEdDHYRKGYjTsQfpV5jyipF";
        nStartMasternodePayments = 1497077275; //Wed, 25 Jun 2014 20:36:16 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xca;
        pchMessageStart[3] = 0xff;
        vAlertPubKey = ParseHex("04201ba1cad0cf49ed56dbd95ec22e5ff392a756a0e6e69d9f455cb9ebabbd96cc287ad65df52bdd84e25cac8ea6b08770c7e332dfc2a218f111ac884b0d6449be");
        nDefaultPort = 19999;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // Fortcoin: 1 day
        nTargetSpacing = 40; // Fortcoin: 2.5 minutes

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1390666206;
        genesis.nNonce = 3861367235;

        hashGenesisBlock = genesis.GetHash();

        vFixedSeeds.clear();
        vSeeds.clear();

      	vSeeds.push_back(CDNSSeedData("149.56.154.90","149.56.154.90"));
        vSeeds.push_back(CDNSSeedData("158.69.238.195","158.69.238.195"));
        vSeeds.push_back(CDNSSeedData("158.69.238.196","158.69.238.196"));
        vSeeds.push_back(CDNSSeedData("192.99.217.80","192.99.217.80"));
        vSeeds.push_back(CDNSSeedData("37.59.209.70","37.59.209.70"));
        vSeeds.push_back(CDNSSeedData("37.59.209.71","37.59.209.71"));
        vSeeds.push_back(CDNSSeedData("151.80.2.241","151.80.2.241"));
        vSeeds.push_back(CDNSSeedData("151.80.2.242","151.80.2.242"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,16);
        // Fortcoin script addresses start with '7'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,76);
        // Fortcoin private keys start with '7' or 'X'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,204);
        // Fortcoin BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Fortcoin BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Fortcoin BIP44 coin type is '5'
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();


        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04201ba1cad0cf49ed56dbd95ec22e5ff392a756a0e6e69d9f455cb9ebabbd96cc287ad65df52bdd84e25cac8ea6b08770c7e332dfc2a218f111ac884b0d6449be";
        strMasternodePaymentsPubKey = "04201ba1cad0cf49ed56dbd95ec22e5ff392a756a0e6e69d9f455cb9ebabbd96cc287ad65df52bdd84e25cac8ea6b08770c7e332dfc2a218f111ac884b0d6449be";
        strDarksendPoolDummyAddress = "y1EZuxhhNMAUofTBEeLqGE1bJrpC2TWRNp";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Fortcoin: 1 day
        nTargetSpacing = 2.5 * 60; // Fortcoin: 2.5 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1417713337;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 1096447;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19994;

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
