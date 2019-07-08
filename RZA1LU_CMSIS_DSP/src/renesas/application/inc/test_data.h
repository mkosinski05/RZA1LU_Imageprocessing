
#define NUMBER_OF_SAMPLES_MAX   (256)
#define MAX_BLOCK_SIZE          (4096)
#define MAX_NUMSTAGE            (65*5)

extern float32_t    SrcF32_A[NUMBER_OF_SAMPLES_MAX];
extern float32_t    SrcF32_B[NUMBER_OF_SAMPLES_MAX];
extern float32_t    SrcF32_D [NUMBER_OF_SAMPLES_MAX * 2];
extern float32_t    SrcF32_D2[NUMBER_OF_SAMPLES_MAX * 2];
extern float32_t    SrcF32_E [NUMBER_OF_SAMPLES_MAX * 2];
extern float32_t    SrcF32_E2[NUMBER_OF_SAMPLES_MAX * 2];
extern float32_t    SrcF32_N[NUMBER_OF_SAMPLES_MAX];
extern float32_t    CoeffsF32_iir[MAX_NUMSTAGE];
extern float32_t    SrcF32_RA[NUMBER_OF_SAMPLES_MAX * 8];
extern float32_t    SrcF32_RB[NUMBER_OF_SAMPLES_MAX * 8];
extern float32_t    testInput_f32[32];
extern q31_t        testInput_q31[32];
extern q15_t        testInput_q15[32];
extern q7_t         testInput_q7[32];

extern q7_t         SrcQ7_A[NUMBER_OF_SAMPLES_MAX];
extern q7_t         SrcQ7_B[NUMBER_OF_SAMPLES_MAX];
extern q7_t         SrcQ7_D [NUMBER_OF_SAMPLES_MAX * 2];
extern q7_t         SrcQ7_E [NUMBER_OF_SAMPLES_MAX * 2];
extern q7_t         SrcQ7_RA[NUMBER_OF_SAMPLES_MAX * 2];
extern q7_t         SrcQ7_RB[NUMBER_OF_SAMPLES_MAX * 2];

extern q15_t        SrcQ15_A[NUMBER_OF_SAMPLES_MAX];
extern q15_t        SrcQ15_B[NUMBER_OF_SAMPLES_MAX];
extern q15_t        SrcQ15_C[NUMBER_OF_SAMPLES_MAX];
extern q15_t        SrcQ15_D [NUMBER_OF_SAMPLES_MAX * 2];
extern q15_t        SrcQ15_E [NUMBER_OF_SAMPLES_MAX * 2];
extern q15_t        SrcQ15_RA[NUMBER_OF_SAMPLES_MAX * 8];
extern q15_t        SrcQ15_RB[NUMBER_OF_SAMPLES_MAX * 8];
extern q15_t        SrcQ15_RC[NUMBER_OF_SAMPLES_MAX * 2];
extern q15_t        SrcQ15_RD[NUMBER_OF_SAMPLES_MAX * 2];

extern q31_t        SrcQ31_A[NUMBER_OF_SAMPLES_MAX];
extern q31_t        SrcQ31_B[NUMBER_OF_SAMPLES_MAX];
extern q31_t        SrcQ31_C[NUMBER_OF_SAMPLES_MAX];
extern q31_t        SrcQ31_D [NUMBER_OF_SAMPLES_MAX * 2];
extern q31_t        SrcQ31_E [NUMBER_OF_SAMPLES_MAX * 2];
extern q31_t        SrcQ31_RA[NUMBER_OF_SAMPLES_MAX * 8];
extern q31_t        SrcQ31_RA2[NUMBER_OF_SAMPLES_MAX * 8];
extern q31_t        SrcQ31_RB[NUMBER_OF_SAMPLES_MAX * 8];
extern q31_t        SrcQ31_RB2[NUMBER_OF_SAMPLES_MAX * 8];

extern float32_t    Sin5kHz_f32[MAX_BLOCK_SIZE];
extern q31_t        Sin5kHz_q31[MAX_BLOCK_SIZE];
extern q15_t        Sin5kHz_q15[MAX_BLOCK_SIZE];

extern float64_t    SrcF64_RA[NUMBER_OF_SAMPLES_MAX * 8];
extern float64_t    SrcF64_RB[NUMBER_OF_SAMPLES_MAX * 8];
