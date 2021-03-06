#include "test.h"

#include "../src/bands.h"
#include "../src/globalvars.h"

// OBJECT ../src/bands.o

/* test conversion from bandindex to bandmask */
void test_toBandMask(void **state) {
    assert_int_equal(inxes[BANDINDEX_160], BAND160);
    assert_int_equal(inxes[BANDINDEX_80], BAND80);
    assert_int_equal(inxes[BANDINDEX_40], BAND40);
    assert_int_equal(inxes[BANDINDEX_30], BAND30);
    assert_int_equal(inxes[BANDINDEX_20], BAND20);
    assert_int_equal(inxes[BANDINDEX_17], BAND17);
    assert_int_equal(inxes[BANDINDEX_15], BAND15);
    assert_int_equal(inxes[BANDINDEX_12], BAND12);
    assert_int_equal(inxes[BANDINDEX_10], BAND10);
    assert_int_equal(inxes[BANDINDEX_OOB], 0);
}

/* test IsWarcIndex */
void test_IsWarcIndex(void **state) {
    assert_int_equal(IsWarcIndex(BANDINDEX_160), 0);
    assert_int_equal(IsWarcIndex(BANDINDEX_80), 0);
    assert_int_equal(IsWarcIndex(BANDINDEX_40), 0);
    assert_int_equal(IsWarcIndex(BANDINDEX_30), 1);
    assert_int_equal(IsWarcIndex(BANDINDEX_20), 0);
    assert_int_equal(IsWarcIndex(BANDINDEX_17), 1);
    assert_int_equal(IsWarcIndex(BANDINDEX_15), 0);
    assert_int_equal(IsWarcIndex(BANDINDEX_12), 1);
    assert_int_equal(IsWarcIndex(BANDINDEX_10), 0);
}

/* test switch to next band UP or DOWN */
void test_nextBandUp(void **state) {
    bandinx = BANDINDEX_12;
    next_band(BAND_UP);
    assert_int_equal(bandinx, BANDINDEX_10);
}

void test_nextBandDown(void **state) {
    bandinx = BANDINDEX_12;
    next_band(BAND_DOWN);
    assert_int_equal(bandinx, BANDINDEX_15);
}

void test_nextBandWrapUpwards(void **state) {
    bandinx = BANDINDEX_10;
    next_band(BAND_UP);
    assert_int_equal(bandinx, BANDINDEX_160);
}

void test_nextBandWrapDownwards(void **state) {
    bandinx = BANDINDEX_160;
    next_band(BAND_DOWN);
    assert_int_equal(bandinx, BANDINDEX_10);
}

/* test conversion from bandmap.c */
void test_conv_f2b_out_of_band(void ** state) {
    assert_int_equal(freq2band(5000000),BANDINDEX_OOB);
}

void test_conv_f2b_borders(void ** state) {
    assert_int_equal(freq2band(1799999),BANDINDEX_OOB);
    assert_int_equal(freq2band(2000001),BANDINDEX_OOB);
    assert_int_equal(freq2band(1800000),0);
    assert_int_equal(freq2band(2000000),0);
}

void test_conv_f2b(void ** state) {
    assert_int_equal(freq2band(1830000),0);
    assert_int_equal(freq2band(3510000),1);
    assert_int_equal(freq2band(7020000),2);
    assert_int_equal(freq2band(10110000),3);
    assert_int_equal(freq2band(14100000),4);
    assert_int_equal(freq2band(18070000),5);
    assert_int_equal(freq2band(21200000),6);
    assert_int_equal(freq2band(24890000),7);
    assert_int_equal(freq2band(28300000),8);
}
