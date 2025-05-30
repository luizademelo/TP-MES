
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/lex/round_trip.h"

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "upb/port/def.inc"

static void upb_FixLocale(char* p) {

  for (; *p; p++) {
    if (*p == ',') *p = '.';
  }
}

void _upb_EncodeRoundTripDouble(double val, char* buf, size_t size) {
  assert(size >= kUpb_RoundTripBufferSize);
  if (isnan(val)) {
    snprintf(buf, size, "%s", "nan");
    return;
  }
  snprintf(buf, size, "%.*g", DBL_DIG, val);
  if (strtod(buf, NULL) != val) {
    snprintf(buf, size, "%.*g", DBL_DIG + 2, val);
    assert(strtod(buf, NULL) == val);
  }
  upb_FixLocale(buf);
}

void _upb_EncodeRoundTripFloat(float val, char* buf, size_t size) {
  assert(size >= kUpb_RoundTripBufferSize);
  if (isnan(val)) {
    snprintf(buf, size, "%s", "nan");
    return;
  }
  snprintf(buf, size, "%.*g", FLT_DIG, val);
  if (strtof(buf, NULL) != val) {
    snprintf(buf, size, "%.*g", FLT_DIG + 3, val);
    assert(strtof(buf, NULL) == val);
  }
  upb_FixLocale(buf);
}
