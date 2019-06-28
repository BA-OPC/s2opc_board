/*
 * Licensed to Systerel under one or more contributor license
 * agreements. See the NOTICE file distributed with this work
 * for additional information regarding copyright ownership.
 * Systerel licenses this file to you under the Apache
 * License, Version 2.0 (the "License"); you may not use this
 * file except in compliance with the License. You may obtain
 * a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "check_crypto_certificates.h"

#include <stdlib.h>

#include <check.h>

#include "hexlify.h"

// server_2k_cert.der
const char* SRV_CRT =
    "30820505308202eda003020102020200fc300d06092a864886f70d01010b0500308193310b3009060355040613024652310f300d0603550408"
    "0c064672616e63653111300f060355040a0c08537973746572656c3136303406035504030c2d53324f50432043656e74757279204365727469"
    "66696361746520417574686f7269747920666f722054657374733128302606092a864886f70d010901161973326f70632d737570706f727440"
    "737973746572656c2e66723020170d3138313030343135343831365a180f32313138303931303135343831365a3066310b3009060355040613"
    "024652310f300d06035504080c064672616e63653111300f060355040a0c08537973746572656c3133303106035504030c2a53324f50432043"
    "656e7475727920436572746966696361746520666f722054657374205365727665727330820122300d06092a864886f70d0101010500038201"
    "0f003082010a02820101009bb3fce0a5805a868035e5b1bbe161af33be4596c9029fe7289e3c4852c9ada105425f96bf732941123e6de1a735"
    "cc644229e895e35ba4180c37efe705f1376be650c8f4c6e126cea0f80d52a033cf7683e127a1e6ae336bb0789c48fe82bd0bc65ac533ea7a60"
    "5739c07376cef6088cf881ee52eb6ae04fc6dc10cd7059a1b8551531721d71486bbb8fba8f1d2898cfca991dff31c71da7f72b08303b453fff"
    "bb171117ecced93309233fe1172fcb6184b76d6d055671ba56d2d561f08ca2828f97c72c10899c603127fc98725a1b8184a1a49b84332400d2"
    "3d92f3fd5a8b75905b3facbbf72e3b80cde86abecf506e5f4e751fe2fd3d169eb02d5674efc6af0203010001a3818c308189301d0603551d0e"
    "041604146745aacc412541d8e1d55021fd83e577a3f4e3ea301f0603551d230418301680147a46cbd22f30a4ff672913393f9c02bf03d07282"
    "300f0603551d130101ff040530030101ff300b0603551d0f04040302010630290603551d1104223020861375726e3a53324f50433a6c6f6361"
    "6c686f737482096c6f63616c686f7374300d06092a864886f70d01010b05000382020100b6919ef62ecae7181b6852ddf904a84dd15781694a"
    "60ad78ed115c181a5af8108200a852d9feb85665dafc76604e733ddffa6f4a9d62b141d6b97a89da9c66b52d043686d46d3d4a88c20cc07102"
    "afcd61abd87685065df99eeecdb682948409219d3d8fcd3d3a0f0ddc6665111da5a11d6f72a6067be11e8804b994d4580be6ec59e77b3895be"
    "ec5fd7929504b15c1d63f98c13757a156cf3d774aaee4b6bc2c1d241f7011a483c752e74b93402609d33a69e974ce9086733e29c112cc7c5e7"
    "f405b6d819309b7acea5a325045f4e322b26ed17718ee409354dc1072679f7dc8a0529ba5d1ee72e7beb0877e06d6ba37ba25fa98783d072e8"
    "c0b510b174ef7051503007699f6914cc3ad976bd334e50b97c69c614ef44469b7c1bc156e3b71fcd6016daf4a1761a29d154d001df7b7e3fc1"
    "402a4d4148e61f58debf30dd43436797d42a763439d2a15d276102d4f19106af8330b37106af5c6156046ca0583d631abe86552cecfa121e80"
    "311153361db385fae6de61c733b6d9f1ff59e8110a02f0802e08de941597fc955fd4b6b18c976379986fcadf95dfa45320e7f6ae81bb144f8f"
    "07a2b416b2eb68ca9d19c0acfdea265f8b488cbc6b5cf51794353afa7e7e52da6ff8445bc60e7a6959b8cffc131d8af47484609bcbcee3fcde"
    "73c876fb1b4b9806a71d75124ab5082673a49f85ae629abc8fb339f685009a38693517";

const char* SRV_CRT_THUMB = "c6c2b0a7f627b8d0fd6166631d1be00e186119f5";

// cacert.der
#define CA_CRT_DEFINE                                                                                                  \
    "3082060d308203f5a003020102020900a0b70a15c7b77114300d06092a864886f70d01010b0500308193310b300906035504061302465231" \
    "0f300d06035504080c064672616e63653111300f060355040a0c08537973746572656c3136303406035504030c2d53324f50432043656e74" \
    "75727920436572746966696361746520417574686f7269747920666f722054657374733128302606092a864886f70d010901161973326f70" \
    "632d737570706f727440737973746572656c2e66723020170d3138313030343135343735375a180f32313138303931303135343735375a30" \
    "8193310b3009060355040613024652310f300d06035504080c064672616e63653111300f060355040a0c08537973746572656c3136303406" \
    "035504030c2d53324f50432043656e7475727920436572746966696361746520417574686f7269747920666f722054657374733128302606" \
    "092a864886f70d010901161973326f70632d737570706f727440737973746572656c2e667230820222300d06092a864886f70d0101010500" \
    "0382020f003082020a0282020100cfd7b7f13562f1c163e6055bc458c6ed53675feb7b7ca0e8688d4c3ad603a5fe5d854d1667691f9e8e35" \
    "03bea1bedccfb6fc58142bd55a379a4c010782df96fb455e467aa785aec3f9d20f86340477c183235533f8d4522e12e0cbcbf4e61cc8f80f" \
    "6266311c8647020a9eb339debb2e9c8887a841b4a172cfaf2084fdeaa4d5d7d33f711b4f2eee441a549b62dad6bd6631221677dede027c85" \
    "b39fdd6461b7e5696a2f8c1d2273de1e4d796cade386008d41a6ee2f540d4823277c049e9c8f3ccfb7f35d8953d862c10e29ffcbb727abe4" \
    "b37735ad069fa2cfa2e9c7344e0a3a0202fccb4a8798bb7e7c6668bc678c29ea5387be9738674228294b99635c57bb376a101d83a655def9" \
    "b298ab56bbee95be80d53e9c2eeffaf44f1fc31ad6aa1d3da59b154eea7e09bbdb897414097b15d0cfe35a7bc85ad85b4c43d8b74befc4df" \
    "fff3731e459035b5d75b288960a7be2f7caedad2fb7f427d9f923bc6e9bb0d6dde17e408e024c3eb44b0d006c37cd5b3353d8579acc3e7c0" \
    "75de712ae6ae819e054012871f43ff3064ac06538c17ac1e7644f3858d62318039e49cf566b40fe3d4e8981fdeacef039e6726312f8612d8" \
    "8da145fdf55d99f5b336bca673938e426bf25638540c2e80c7af5b8522c30795c74b14af1059c62acb0fa79e563cc907a997155654942cdf" \
    "9dafac4fc9c14f66838eb766539d9843ebb5f93506450203010001a360305e301d0603551d0e041604147a46cbd22f30a4ff672913393f9c" \
    "02bf03d07282301f0603551d230418301680147a46cbd22f30a4ff672913393f9c02bf03d07282300f0603551d130101ff040530030101ff" \
    "300b0603551d0f040403020106300d06092a864886f70d01010b050003820201001fbc525a496d0fab7a62e6074dd994c8c9bdeeb11a34aa" \
    "9f3203c53604826991ca1d02a31c28f9add8dddf63681180902bc5a04a2256c4ea28d44e2343b53af6951db2dce9bffaee596e3fc21f0b02" \
    "58f77f0af3fef4e1bc0d8862d67c8e5c230146be593913bc3ad96807896472f521e4adb74b0af3efeadb48a173a10fcc67577e0dff2feef3" \
    "556e36689dbff5891b95506ea00d2b265a488895a3f66bf4b623466c2f5831c6a58ee455936a620db9f819870a23ee213db19c2fff3ca0c2" \
    "62f22928d1f8c62e8c4aec5e3acdc750e5d44c8c3b43f85a6781b8ae373781f72955389f066e5aca009fece8bd8733ac2ed1250b99c6a95c" \
    "4c0b0cf546cc55c6467f13709e5313ea64872c8ae385e321d3530c21412e061f8c22b6696fc80419bc5901b7424e28fca6721f57c98cfa26" \
    "486e0937764a1ab90be7d59c7ba06eb3cba08d640163a046f2a3aaf23fd783d056af1cae590fff8e1491eefca95c12f3943b8c3876cdf18f" \
    "cd31f03a9a055348e20514397beff7e236aa1b869035b861072aa5bac49af41e4fac8ed8a876fcbeb4b02ab256d9027241d7d2b6167e686a" \
    "328bdc5b16901bf48a0d1448d9a959a8df34f05382d1a00502a18667a16456a0c845c543e899b78959559a6c5543f7067dcebb88c14f6469" \
    "8750488a3fb60a2163d7d504aa470e9c96c69c9fc5ccd84484122743c2c2e5d4df6af8de8952561eb6"

const char* CA_CRT = CA_CRT_DEFINE;
const size_t CA_CRT_LEN = sizeof(CA_CRT_DEFINE) / 2;

SOPC_Certificate* SOPC_UnhexlifyCertificate(const char* hex_data)
{
    size_t der_len = strlen(hex_data) / 2;
    uint8_t* der_data = SOPC_Calloc(der_len, sizeof(uint8_t));
    ck_assert_ptr_nonnull(der_data);

    ck_assert(unhexlify(hex_data, der_data, der_len) == (int) der_len);
    SOPC_Certificate* crt = NULL;
    ck_assert(der_len <= SIZE_MAX);
    ck_assert_uint_eq(SOPC_STATUS_OK, SOPC_KeyManager_Certificate_CreateFromDER(der_data, (uint32_t) der_len, &crt));
    SOPC_Free(der_data);

    return crt;
}
