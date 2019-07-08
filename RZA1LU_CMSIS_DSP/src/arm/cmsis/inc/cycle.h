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
#define EVTSEL0 0x01        // 命令キャッシュミス
#define EVTSEL1 0x03        // データキャッシュミス
#if 0
#define EVTSELx 0x04        // データキャッシュへのアクセス
#define EVTSELx 0x10        // 予測に失敗したか、予測されなかった分岐
#define EVTSELx 0x60        // 命令キャッシュ依存ストールサイクル (近似)
#define EVTSELx 0x61        // データキャッシュ依存ストールサイクル (近似)
#endif
#define EVTSEL2 0x66        // 発行で命令がディスパッチされない (正確)
#define EVTSEL3 0x67        // 発行が空 (正確)
#if 0
#define EVTSELx 0x70        // メイン実行ユニット命令
#define EVTSELx 0x71        // 第2実行ユニット命令
#define EVTSELx 0x72        // ロード/ ストア命令
#endif
#define EVTSEL4 0x73        // 浮動小数点命令 (近似)
#define EVTSEL5 0x74        // NEON命令 (近似)
#if 0
#define EVTSELx 0x8a        // 整数クロック稼働
#endif

static __inline void pmon_initial_cycle_counter ( void );
static __inline void pmon_start_cycle_counter ( void );
static __inline long pmon_read_cycle_counter ( void );
static __inline void pmon_read_pmc_counter ( unsigned int *value );

static __inline void pmon_initial_cycle_counter ( void )
{
    unsigned long x;

#if defined(__GNUC__)
    x = 0;                                              // カウンタ0 を選択
    __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(x));  // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
    x = EVTSEL0;                                        // イベント0設定
    __asm__ ("MCR p15, 0, %0, c9, c13, 1" : : "r"(x));  // EVTSEL0(イベント選択0)レジスタ書き込み

    x = 1;                                              // カウンタ1を選択
    __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(x));  // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
    x = EVTSEL1;                                        // イベント1設定
    __asm__ ("MCR p15, 0, %0, c9, c13, 1" : : "r"(x));  // EVTSEL1(イベント選択1)レジスタ書き込み

    x = 2;                                              // カウンタ2 を選択
    __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(x));  // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
    x = EVTSEL2;                                        // イベント2設定
    __asm__ ("MCR p15, 0, %0, c9, c13, 1" : : "r"(x));  // EVTSEL2(イベント選択2)レジスタ書き込み

    x = 3;                                              // カウンタ3を選択
    __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(x));  // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
    x = EVTSEL3;                                        // イベント3設定
    __asm__ ("MCR p15, 0, %0, c9, c13, 1" : : "r"(x));  // EVTSEL3(イベント選択3)レジスタ書き込み

    x = 4;                                              // カウンタ4を選択
    __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(x));  // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
    x = EVTSEL4;                                        // イベント4設定
    __asm__ ("MCR p15, 0, %0, c9, c13, 1" : : "r"(x));  // EVTSEL4(イベント選択4)レジスタ書き込み

    x = 5;                                              // カウンタ5を選択
    __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(x));  // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
    x = EVTSEL5;                                        // イベント5設定
    __asm__ ("MCR p15, 0, %0, c9, c13, 1" : : "r"(x));  // EVTSEL5(イベント選択5)レジスタ書き込み

    x = (   (1ul << PMCNTENSET_C) |         // サイクルカウンタ 稼働
            (1ul << PMCNTENSET_P5) |        // パフォーマンスカウンタ5 稼働
            (1ul << PMCNTENSET_P4) |        // パフォーマンスカウンタ4 稼働
            (1ul << PMCNTENSET_P3) |        // パフォーマンスカウンタ3 稼働
            (1ul << PMCNTENSET_P2) |        // パフォーマンスカウンタ2 稼働
            (1ul << PMCNTENSET_P1) |        // パフォーマンスカウンタ1 稼働
            (1ul << PMCNTENSET_P0) );       // パフォーマンスカウンタ0 稼働
    __asm__ ("MCR   p15, 0, %0, c9, c12, 1" : : "r"(x));    // CNTENS(カウントイネーブルセット)レジスタ書き込み
#else
    x = 0;                                  // カウンタ0 を選択
    __asm ("MCR p15, 0, x, c9, c12, 5");    // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
    x = EVTSEL0;                            // イベント0設定
    __asm ("MCR p15, 0, x, c9, c13, 1");    // EVTSEL0(イベント選択0)レジスタ書き込み

    x = 1;                                  // カウンタ1を選択
    __asm ("MCR p15, 0, x, c9, c12, 5");    // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
    x = EVTSEL1;                            // イベント1設定
    __asm ("MCR p15, 0, x, c9, c13, 1");    // EVTSEL1(イベント選択1)レジスタ書き込み

    x = 2;                                  // カウンタ2 を選択
    __asm ("MCR p15, 0, x, c9, c12, 5");    // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
    x = EVTSEL2;                            // イベント2設定
    __asm ("MCR p15, 0, x, c9, c13, 1");    // EVTSEL2(イベント選択2)レジスタ書き込み

    x = 3;                                  // カウンタ3を選択
    __asm ("MCR p15, 0, x, c9, c12, 5");    // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
    x = EVTSEL3;                            // イベント3設定
    __asm ("MCR p15, 0, x, c9, c13, 1");    // EVTSEL3(イベント選択3)レジスタ書き込み

    x = 4;                                  // カウンタ4を選択
    __asm ("MCR p15, 0, x, c9, c12, 5");    // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
    x = EVTSEL4;                            // イベント4設定
    __asm ("MCR p15, 0, x, c9, c13, 1");    // EVTSEL4(イベント選択4)レジスタ書き込み

    x = 5;                                  // カウンタ5を選択
    __asm ("MCR p15, 0, x, c9, c12, 5");    // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
    x = EVTSEL5;                            // イベント5設定
    __asm ("MCR p15, 0, x, c9, c13, 1");    // EVTSEL5(イベント選択5)レジスタ書き込み

    x = (   (1ul << PMCNTENSET_C) |         // サイクルカウンタ 稼働
            (1ul << PMCNTENSET_P5) |        // パフォーマンスカウンタ5 稼働
            (1ul << PMCNTENSET_P4) |        // パフォーマンスカウンタ4 稼働
            (1ul << PMCNTENSET_P3) |        // パフォーマンスカウンタ3 稼働
            (1ul << PMCNTENSET_P2) |        // パフォーマンスカウンタ2 稼働
            (1ul << PMCNTENSET_P1) |        // パフォーマンスカウンタ1 稼働
            (1ul << PMCNTENSET_P0) );       // パフォーマンスカウンタ0 稼働
    __asm ("MCR p15, 0, x, c9, c12, 1");    // CNTENS(カウントイネーブルセット)レジスタ書き込み
#endif
}

static __inline void pmon_start_cycle_counter ( void )
{
    unsigned long x;

#if defined(__GNUC__)
    __asm__ ("MRC   p15, 0, %0, c9, c12, 0" : "=r"(x)); // PMNC(パフォーマンスモニタ制御)レジスタ読み出し
    x |= (  (0 << PMCR_D) |                 // サイクルカウント ディバイダ:
                                            //  0 = プロセッサのすべてのクロックサイクルをカウントする。これはリセット時の値です。
                                            //  1 = プロセッサのクロックを64 サイクルごとにカウントする。
            (1 << PMCR_C) |                 // サイクルカウンタのリセット。
            (1 << PMCR_P) |                 // イベントカウンタのリセット。
            (1 << PMCR_E));                 // イネーブルビット。
    __asm__ ("MCR   p15, 0, %0, c9, c12, 0" : : "r"(x));    // PMNC(パフォーマンスモニタ制御)レジスタ書き込み
#else
    __asm ("MRC p15, 0, x, c9, c12, 0");    // PMNC(パフォーマンスモニタ制御)レジスタ読み出し
    x |= (  (0 << PMCR_D) |                 // サイクルカウント ディバイダ:
                                            //  0 = プロセッサのすべてのクロックサイクルをカウントする。これはリセット時の値です。
                                            //  1 = プロセッサのクロックを64 サイクルごとにカウントする。
            (1 << PMCR_C) |                 // サイクルカウンタのリセット。
            (1 << PMCR_P) |                 // イベントカウンタのリセット。
            (1 << PMCR_E));                 // イネーブルビット。
    __asm ("MCR p15, 0, x, c9, c12, 0");    // PMNC(パフォーマンスモニタ制御)レジスタ書き込み
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
        __asm__ ("MCR p15, 0, %0, c9, c12, 5" : : "r"(id));     // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
        __asm__ ("MRC p15, 0, %0, c9, c13, 2" : "=r"(x));       // PMNx(パフォーマンスモニタカウント)レジスタ読み出し
#else
        __asm ("MCR p15, 0, id, c9, c12, 5");   // PMNXSEL(パフォーマンスカウンタ選択)レジスタ書き込み
        __asm ("MRC p15, 0, x, c9, c13, 2");    // PMNx(パフォーマンスモニタカウント)レジスタ読み出し
#endif
        *value++ = x;
    }
}
