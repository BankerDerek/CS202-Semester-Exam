main: main.cpp WavFileIO.o WavFileIO.h GainAdjustment.o GainAdjustment.h LowPassFilter.o LowPassFilter.h normalization.o normalization.h 
	g++ -o AudioProcessor.exe main.cpp WavFileIO.o GainAdjustment.o LowPassFilter.o normalization.o
WavFileIO.o: WavFileIO.cpp WavFileIO.h
	g++ -c WavFileIO.cpp
GainAdjustment.o: GainAdjustment.cpp GainAdjustment.h
	g++ -c GainAdjustment.cpp
LowPassFilter.o: LowPassFilter.cpp LowPassFilter.h
	g++ -c LowPassFilter.cpp
normalization.o: normalization.cpp normalization.h
	g++ -c normalization.cpp
clean: 
	del *.o *.exe *exe.core