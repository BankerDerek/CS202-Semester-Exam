main: main.cpp AudioProcessor.o AudioProcessor.h LowPassFilter.o LowPassFilter.h GainAdjustment.o GainAdjustment.h Normalization.o Normalization.h Compression.o Compression.h Echo.o Echo.h WavFileIO.o WavFileIO.h
	g++ -o AudioProcessor.exe main.cpp AudioProcessor.o LowPassFilter.o GainAdjustment.o Normalization.o Compression.o Echo.o WavFileIO.o   
AudioProcessor.o: AudioProcessor.cpp AudioProcessor.h
	g++ -c AudioProcessor.cpp
LowPassFilter.o: LowPassFilter.cpp LowPassFilter.h
	g++ -c LowPassFilter.cpp
GainAdjustment.o: GainAdjustment.cpp GainAdjustment.h
	g++ -c GainAdjustment.cpp
Normalization.o: Normalization.cpp Normalization.h
	g++ -c Normalization.cpp
Compression.o: Compression.cpp Compression.h
	g++ -c Compression.cpp
Echo.o: Echo.cpp Echo.h
	g++ -c Echo.cpp
WavFileIO.o: WavFileIO.cpp WavFileIO.h
	g++ -c WavFileIO.cpp
clean: 
	del *.o *.exe *exe.core