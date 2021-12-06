//Connor Riche
//AudioProcessor.h

#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H
#include "Echo.h"
#include "GainAdjustment.h"
#include "Normalization.h"
#include "Compression.h"
#include "LowPassFilter.h"

class Process : public Echo, public GainAdjustment, public Normalization, public Compression, public LowPassFilter{};

#endif