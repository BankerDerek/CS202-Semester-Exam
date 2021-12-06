//Connor Riche
//AudioProcessor.h
#include "Echo.h"
#include "GainAdjustment.h"
#include "normalization.h"
#include "Compression.h"
#include "LowPassFilter.h"

class Process : public Echo, public GainAdjustment, public Normalization, public Compression, public LowPassFilter{};
