// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018, The TurtleCoin Developers
// Copyright (c) 2018-2020, The Qwertycoin Group.
//
// This file is part of Qwertycoin.
//
// Qwertycoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Qwertycoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Qwertycoin.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <cstddef>
#include <initializer_list>

namespace CryptoNote {

struct CheckpointData
{
    uint32_t height;
    const char *blockId;
};

const std::initializer_list<CheckpointData> CHECKPOINTS = {
    {     1,"6f783fc255bd66ed936e2aa03ce4ae908ff4e93cd4b7816d2734b92b7ff8f83d"},
    {    10,"28808dcf876eb0d03b97a057c0c140ebc692683e38d946903923212d769aae31"},
    {   100,"7a2fd678850b5513648b89bceac345af2d77739cf3689a4deb49a0e407cd9bb3"},
    {  1000,"ec5920066d972658840a29bf7cb723cf92c35883046538fc04f0604f0ee217b3"},
    { 10000,"fb021fd69f78a60a365c16692777e7f699215404366545e072eba7dddbf1d61d"},
    { 15000,"fb8ad336e6518aa6a5f874a15276561249d36a35afd08f0f1fab78333d9e4149"},
    { 20000,"d32286163e2a5cfbbab35007438e7bf90564afee70c715930606710e96f2ce19"},
    { 25000,"c064cd86be01c32c86e0c7a6295023628acfeaa2786e2873a03343bc6f6a8d41"},
    { 30000,"1d32bbca2149eeb27ff9e2c19d1b6ace4a160764839a4da7031328f7ea49e6f6"},
    { 35000,"173269a8b2ed188ef95a876acaf807cbbc4817191f036063ecf92112f46b5cbf"},
    { 40000,"60a9694b18cf470bcfd9f36f32ad01f86b5538fe1f88a3bd2717ca6ad1c7ce80"},//2.0
    { 45000,"0e504e82e6fe247b0b5dae9fc5bd3e82982e61610fd674d8e1f8ee3c85000c15"},
    { 46000,"51e2f9e09278cb66b08efcecfdf3208053ee53030c6fc5a6a647565a6b318cd5"},//3.0
    { 50000,"5599ca3d8ac58f377187b5a43c00103496244ec95299e4ae3dff3be6016488bf"},
    { 55000,"b90e836c7ad95a6184869f16406161ac541c4ee3f2436447668a7f43362da733"},
    { 60000,"796e0037bed22ec317dc165bdfcc331322fe3fcc7ca162827ab374a7d17107f0"},
    { 65000,"d03c367bc1d87bea553346245ae60865175371b449dea11b79b7cfa28453d892"},
    { 70000,"9b035668d72b17ceaabbd4b341089f090aa5ebad37f33513509d9f6e102c7c0c"},
    { 75000,"dfe99ff9e3eaa55fd24797cd2639e156e5222a10a0c14f690f4007cbe6ce3477"},
    { 80000,"02bdbd6cab951c0685796598b353524d450f947c58d8e1a8efbc05c334663ad7"},
    { 85000,"9b6d12df949ad48cb6dfa178c05eacba072c6e9379fd074dddf723728923fc4b"},
    { 90000,"96e00099a12e4e50a84d361942a05ff026f2e0f413f0f9afefc8af7085dde9da"},
    { 95000,"aa464ea213efa3f41ab1196c54b5bb0e8341d6ee47668b342db55eeafc9e81d0"},
    {100000,"d5b20487d7a4b76d80dc2ae5e51da7feb9190a88264492ecc2f965e4f30b737d"},
    {105000,"b75bc59877f3e47e7fc6b1a019022391d627ed23e3930e5fef544a8176adbf4d"},
    {110520,"a2d08d171265aa0c4ee9e5e5baebd191940f86ccc7b01cd8ebfa2276db98736c"},//4.0
    {120000,"b31f8f2284f51cecf8028876ddd6df7c812b7fbc274ff7bab303f1fcc3b3310b"},
    {125000,"5d551f52c0d36ed11fd1d57261e5be373a17e2fb5b67b9af54e6c3b3b192a1b8"},
    {130000,"7c171f2a4d40a136ba9f309895cc695f957a783736f492a4bb9613905cd62256"},
    {135000,"172e566e640677eb027831030753e6c8b3583602113086381983d0996e83c172"},
    {140000,"60c532ab429aaba8027528d39499fb935d00c53a0b73559a03434b2fc6b01c9f"},
    {145000,"5bb86ade9b4f0a067ed145a4a9141763d882d7b00c84acd9ad90f44014a5bc45"},
    {150000,"0d693d183d662d53101d9729a5e03f4fe87a378c4dacbb642842cdaf6a75c224"},
    {155000,"f6a274a8824b4444626d4abbd23c062051746005cbf0cc596c5983ee9803d2d5"},
    {160000,"d372a4f56bb020bbeef7dc3543ebde9076110bbc3390a70f302a4565743a2fcd"},
    {165000,"602bfcc666229123d242e513339af6cb24fff209f86d485655635b6b1504b580"},
    {173136,"36a9ab5f39cf4a1d612c4e10c1a72b7d147ab88f92e511af84265b7d04804dc0"},//4.0.2
    {180000,"f4b74b907bcf622b4b7353c22886b502fc0e3fdbd71ba6087b9248d80eddbdae"},
    {185000,"d44a75f89bf20ba8c878e2e3ebae688a0cb507e6fda8315009db1128f92ed39c"},
    {190000,"40fce151760a333b81a66c1e41c91d0b804fc7efb7c06fc5f9ecb1e20c8323e7"},
    {195000,"f077b19ab10f65b64c2662682d3629ac382dc6d2d89ee035a6090051756c1c13"},
    {200000,"22d739a610c5cb7ca4a2debd19b4bac38c0e0df2393de67ab131eec0b6537ec2"},
    {205000,"f32f4c63a00d6cf10413cc7d9325a6dad9b83c1062b4842dec90f483b59e4232"},
    {210000,"ced2e2f563172da1805522b443397e9c85ee7a5aa49d5674a2d61b491e0f7e4f"},
    {215000,"feffb1aee118fd1ed8b3b8754ce4145924ecf1d4b74e95d30431b38e67f61605"},
    {220000,"2d7d54263c939bdaba1892946d9292b24cced789cbc5d14b6164ab8b57658f75"},
    {225000,"aecccbbeef7067e1150f7357869a3a47f4f39f84bf90e48cbb9b18c443956ce0"},
    {230000,"190891fd56763afbc9e7c609a3a90bcb801a504daf2e352060cf1f7dfb9f2896"},
    {235000,"11baf2529c8617b9db83378b5cb3666dbfdc5eb3b1ffd9052f69e7d5e9b4a638"},
    {240000,"522cbcb5341a1c4a804212923713227363671a2db3ea41f8957a15b6234b17f4"},
    {245000,"31cd9378eb1031574b504342fd73a6f57be94059d3023fdc7ec564d53de50b24"},
    {250721,"a119b644ec0a35c77f8cf7ed6a0ff4d37b7a279ac8fadfb660e83cc795ddb7de"},//5.0.0
    {255000,"a6d7494587113d76e5c68e309c82e458443fe85383b2a4bdb86bcb82ea2a7345"},
    {260000,"cb4b1fd2734dda8ca121d4bf7e8b8612a1c1e88f26d8aac226caf3f10023b567"},
    {265000,"3439629cd14bcff43240cdd0444cd075fddd411d3a5ad0ce0aadab5434c920f2"},
    {270000,"3b8802ec65b809de52c78dd5c34c27d65fdcf6eaddaf2e295c63958c9061a4b6"},
    {275213,"ba51659f63ef31685c0b9e816d9c3b9455fe20cc34aa8ef09a186153e83547a9"},//5.1.3
    {280000,"c1c98dcc12f58cb5f75b9b2d80977b12f791dacbbdc3dbf7b90d0e4937b34a48"},
    {285000,"7048e6c3b796ce36dea32050f85bb8e8e91febd2fd812ea1a486d921bfba792e"},
    {290000,"b20dbdb3b69b0c5d384ed049ec7e1d7d51b80ade3623f03f1f16c2524bfb6902"},
    {295000,"cd86ab13abf15dacc346d17cbb842c683125d2ab296f9ddb07baffbf7dfbee24"},
    {300000,"a02e87603e60f3186a232e7d8405d4d1d130bfc2d1d007e7beed8c14a09026eb"},
    {305000,"1a2aafc52c02add00d78acbb3fbabbe87764ce0d01808539df7110b3c167f3fe"},
    {308323,"12253186704f9898f390fcfe2550ee98f2331dbf9edda9c55ca8fb218f3eca37"},//5.1.4
    {325000,"8c8171a4c00e57468f485f62cbe777d3dfefa018b5e084fc2986cdd48eeff8bb"},
    {350000,"309e444aa88e588b59c7c9053a552fe76994d52c37648e7da4760aa26fe99301"},
    {375000,"37384327794fb7d825a3dd7186919bc6b0d64063a4919baef540923fdd6642d2"},
    {400000,"c787cfb334eb48560ceffb0402324d9a049f40f54fcd899196d002926b5d374b"},
    {425000,"28b28405a980d2e98920bcd260b027b0ff838acf2311cb1e7b0aa9ea092f53bc"},
    {450000,"d0f32e38d52d9c91ddee93883e07ff95c8d6f415b96ec1eed36b8632776726cd"},
    {475000,"8a6a4dd092ff41167d9c082a5da73323a3c7a46c8539a18018b2275500bd632c"},
    {500000,"432b0c6cfbb5967950efc2f2358f42dc85ddbc5dd270b619cd1f466970a41236"},
    {505000,"e9b2492b83308110e265e77c74bd36735eb9f3f45a78df14d775b65e82eb6c01"}
};

} // namespace CryptoNote
