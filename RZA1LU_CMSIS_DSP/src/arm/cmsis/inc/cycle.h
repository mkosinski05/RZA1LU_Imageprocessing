/* Performance Monitor Control Register of Cortex A9*/
#define PMCR_D 3
#define PMCR_C 2
#define PMCR_P 1
#define PMCR_E 0
#define PMCNTENSET_C 31
#define PMCNTENSET_P5 5
#define PMCNTENSET_P4 4
#define PMCNTENSET_P3 3
#define PMCNTENSET_P2 2
#define PMCNTENSET_P1 1
#define PMCNTENSET_P0 0
#define EVTSEL0 0x01        // ���߃L���b�V���~�X
#define EVTSEL1 0x03        // �f�[�^�L���b�V���~�X
#if 0
#define EVTSELx 0x04        // �f�[�^�L���b�V���ւ̃A�N�Z�X
#define EVTSELx 0x10        // �\���Ɏ��s�������A�\������Ȃ���������
#define EVTSELx 0x60        // ���߃L���b�V���ˑ��X�g�[���T�C�N�� (�ߎ�)
#define EVTSELx 0x61        // �f�[�^�L���b�V���ˑ��X�g�[���T�C�N�� (�ߎ�)
#endif
#define EVTSEL2 0x66        // ���s�Ŗ��߂��f�B�X�p�b�`����Ȃ� (���m)
#define EVTSEL3 0x67        // ���s���� (���m)
#if 0
#define EVTSELx 0x70        // ���C�����s���j�b�g����
#define EVTSELx 0x71        // ��2���s���j�b�g����
#define EVTSELx 0x72        // ���[�h/ �X�g�A����
#endif
#define EVTSEL4 0x73        // ���������_���� (�ߎ�)
#define EVTSEL5 0x74        // NEON���� (�ߎ�)
#if 0
#define EVTSELx 0x8a        // �����N���b�N�ғ�
#endif

static __inline void pmon_initial_cycle_counter ( void );
static __inline void pmon_start_cycle_counter ( void );
static __inline long pmon_read_cycle_counter ( void );
static __inline void pmon_read_pmc_counter ( unsigned int *value );

static __inline void pmon_initial_cycle_counter ( void )
{
    unsigned long x;

#if defined(__GNUC__)
    x = 0;                                              // �J�E���^0 ��I��
    __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(x));  // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
    x = EVTSEL0;                                        // �C�x���g0�ݒ�
    __asm__ ("MCR p15, 0, %0, c9, c13, 1" : : "r"(x));  // EVTSEL0(�C�x���g�I��0)���W�X�^��������

    x = 1;                                              // �J�E���^1��I��
    __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(x));  // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
    x = EVTSEL1;                                        // �C�x���g1�ݒ�
    __asm__ ("MCR p15, 0, %0, c9, c13, 1" : : "r"(x));  // EVTSEL1(�C�x���g�I��1)���W�X�^��������

    x = 2;                                              // �J�E���^2 ��I��
    __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(x));  // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
    x = EVTSEL2;                                        // �C�x���g2�ݒ�
    __asm__ ("MCR p15, 0, %0, c9, c13, 1" : : "r"(x));  // EVTSEL2(�C�x���g�I��2)���W�X�^��������

    x = 3;                                              // �J�E���^3��I��
    __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(x));  // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
    x = EVTSEL3;                                        // �C�x���g3�ݒ�
    __asm__ ("MCR p15, 0, %0, c9, c13, 1" : : "r"(x));  // EVTSEL3(�C�x���g�I��3)���W�X�^��������

    x = 4;                                              // �J�E���^4��I��
    __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(x));  // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
    x = EVTSEL4;                                        // �C�x���g4�ݒ�
    __asm__ ("MCR p15, 0, %0, c9, c13, 1" : : "r"(x));  // EVTSEL4(�C�x���g�I��4)���W�X�^��������

    x = 5;                                              // �J�E���^5��I��
    __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(x));  // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
    x = EVTSEL5;                                        // �C�x���g5�ݒ�
    __asm__ ("MCR p15, 0, %0, c9, c13, 1" : : "r"(x));  // EVTSEL5(�C�x���g�I��5)���W�X�^��������

    x = (   (1ul << PMCNTENSET_C) |         // �T�C�N���J�E���^ �ғ�
            (1ul << PMCNTENSET_P5) |        // �p�t�H�[�}���X�J�E���^5 �ғ�
            (1ul << PMCNTENSET_P4) |        // �p�t�H�[�}���X�J�E���^4 �ғ�
            (1ul << PMCNTENSET_P3) |        // �p�t�H�[�}���X�J�E���^3 �ғ�
            (1ul << PMCNTENSET_P2) |        // �p�t�H�[�}���X�J�E���^2 �ғ�
            (1ul << PMCNTENSET_P1) |        // �p�t�H�[�}���X�J�E���^1 �ғ�
            (1ul << PMCNTENSET_P0) );       // �p�t�H�[�}���X�J�E���^0 �ғ�
    __asm__ ("MCR   p15, 0, %0, c9, c12, 1" : : "r"(x));    // CNTENS(�J�E���g�C�l�[�u���Z�b�g)���W�X�^��������
#else
    x = 0;                                  // �J�E���^0 ��I��
    __asm ("MCR p15, 0, x, c9, c12, 5");    // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
    x = EVTSEL0;                            // �C�x���g0�ݒ�
    __asm ("MCR p15, 0, x, c9, c13, 1");    // EVTSEL0(�C�x���g�I��0)���W�X�^��������

    x = 1;                                  // �J�E���^1��I��
    __asm ("MCR p15, 0, x, c9, c12, 5");    // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
    x = EVTSEL1;                            // �C�x���g1�ݒ�
    __asm ("MCR p15, 0, x, c9, c13, 1");    // EVTSEL1(�C�x���g�I��1)���W�X�^��������

    x = 2;                                  // �J�E���^2 ��I��
    __asm ("MCR p15, 0, x, c9, c12, 5");    // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
    x = EVTSEL2;                            // �C�x���g2�ݒ�
    __asm ("MCR p15, 0, x, c9, c13, 1");    // EVTSEL2(�C�x���g�I��2)���W�X�^��������

    x = 3;                                  // �J�E���^3��I��
    __asm ("MCR p15, 0, x, c9, c12, 5");    // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
    x = EVTSEL3;                            // �C�x���g3�ݒ�
    __asm ("MCR p15, 0, x, c9, c13, 1");    // EVTSEL3(�C�x���g�I��3)���W�X�^��������

    x = 4;                                  // �J�E���^4��I��
    __asm ("MCR p15, 0, x, c9, c12, 5");    // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
    x = EVTSEL4;                            // �C�x���g4�ݒ�
    __asm ("MCR p15, 0, x, c9, c13, 1");    // EVTSEL4(�C�x���g�I��4)���W�X�^��������

    x = 5;                                  // �J�E���^5��I��
    __asm ("MCR p15, 0, x, c9, c12, 5");    // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
    x = EVTSEL5;                            // �C�x���g5�ݒ�
    __asm ("MCR p15, 0, x, c9, c13, 1");    // EVTSEL5(�C�x���g�I��5)���W�X�^��������

    x = (   (1ul << PMCNTENSET_C) |         // �T�C�N���J�E���^ �ғ�
            (1ul << PMCNTENSET_P5) |        // �p�t�H�[�}���X�J�E���^5 �ғ�
            (1ul << PMCNTENSET_P4) |        // �p�t�H�[�}���X�J�E���^4 �ғ�
            (1ul << PMCNTENSET_P3) |        // �p�t�H�[�}���X�J�E���^3 �ғ�
            (1ul << PMCNTENSET_P2) |        // �p�t�H�[�}���X�J�E���^2 �ғ�
            (1ul << PMCNTENSET_P1) |        // �p�t�H�[�}���X�J�E���^1 �ғ�
            (1ul << PMCNTENSET_P0) );       // �p�t�H�[�}���X�J�E���^0 �ғ�
    __asm ("MCR p15, 0, x, c9, c12, 1");    // CNTENS(�J�E���g�C�l�[�u���Z�b�g)���W�X�^��������
#endif
}

static __inline void pmon_start_cycle_counter ( void )
{
    unsigned long x;

#if defined(__GNUC__)
    __asm__ ("MRC   p15, 0, %0, c9, c12, 0" : "=r"(x)); // PMNC(�p�t�H�[�}���X���j�^����)���W�X�^�ǂݏo��
    x |= (  (0 << PMCR_D) |                 // �T�C�N���J�E���g �f�B�o�C�_:
                                            //  0 = �v���Z�b�T�̂��ׂẴN���b�N�T�C�N�����J�E���g����B����̓��Z�b�g���̒l�ł��B
                                            //  1 = �v���Z�b�T�̃N���b�N��64 �T�C�N�����ƂɃJ�E���g����B
            (1 << PMCR_C) |                 // �T�C�N���J�E���^�̃��Z�b�g�B
            (1 << PMCR_P) |                 // �C�x���g�J�E���^�̃��Z�b�g�B
            (1 << PMCR_E));                 // �C�l�[�u���r�b�g�B
    __asm__ ("MCR   p15, 0, %0, c9, c12, 0" : : "r"(x));    // PMNC(�p�t�H�[�}���X���j�^����)���W�X�^��������
#else
    __asm ("MRC p15, 0, x, c9, c12, 0");    // PMNC(�p�t�H�[�}���X���j�^����)���W�X�^�ǂݏo��
    x |= (  (0 << PMCR_D) |                 // �T�C�N���J�E���g �f�B�o�C�_:
                                            //  0 = �v���Z�b�T�̂��ׂẴN���b�N�T�C�N�����J�E���g����B����̓��Z�b�g���̒l�ł��B
                                            //  1 = �v���Z�b�T�̃N���b�N��64 �T�C�N�����ƂɃJ�E���g����B
            (1 << PMCR_C) |                 // �T�C�N���J�E���^�̃��Z�b�g�B
            (1 << PMCR_P) |                 // �C�x���g�J�E���^�̃��Z�b�g�B
            (1 << PMCR_E));                 // �C�l�[�u���r�b�g�B
    __asm ("MCR p15, 0, x, c9, c12, 0");    // PMNC(�p�t�H�[�}���X���j�^����)���W�X�^��������
#endif
}

static __inline long pmon_read_cycle_counter ( void )
{
    unsigned long x;

#if defined(__GNUC__)
    __asm__ ("MRC   p15, 0, %0, c9, c13, 0" : "=r"(x));
#else
#if 1
    __asm ("MRC p15, 0, x, c9, c13, 0");
#else
    x = 0;
#endif
#endif
    return x;
}

static __inline void pmon_read_pmc_counter ( unsigned int *value )
{
    long id;
    unsigned long x;

    for (id = 0; id < 6; id++) {
#if defined(__GNUC__)
        __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(id));     // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
        __asm__ ("MRC p15, 0, %0, c9, c13, 2" : "=r"(x));       // PMNx(�p�t�H�[�}���X���j�^�J�E���g)���W�X�^�ǂݏo��
#else
        __asm ("MCR p15, 0, id, c9, c12, 5");   // PMNXSEL(�p�t�H�[�}���X�J�E���^�I��)���W�X�^��������
        __asm ("MRC p15, 0, x, c9, c13, 2");    // PMNx(�p�t�H�[�}���X���j�^�J�E���g)���W�X�^�ǂݏo��
#endif
        *value++ = x;
    }
}
