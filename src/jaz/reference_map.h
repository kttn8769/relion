#ifndef REFERENCE_MAP_H
#define REFERENCE_MAP_H

#include <src/image.h>
#include <src/projector.h>
#include <vector>

class ObservationModel;

class ReferenceMap
{
    public:

        typedef enum {Own, Opposite} HalfSet;

        ReferenceMap();

            // input parameters:
            std::string reconFn0, reconFn1, maskFn, fscFn;
            double paddingFactor;

            // data:
            Image<RFLOAT> freqWeight;
            std::vector<double> freqWeight1D;
            Projector projectors[2];
            Image<RFLOAT> maps[2], powSpec[2];
            int k_out;

        void read(IOParser& parser, int argc, char *argv[]);
        void load(int verb, bool debug);

        std::vector<Image<Complex>> predictAll(
                const MetaDataTable& mdt,
                const ObservationModel& obs,
                HalfSet hs, int threads,
                bool applyCtf = true,
                bool applyTilt = true);

        Image<Complex> predict(
                const MetaDataTable& mdt, int p,
                const ObservationModel& obs,
                HalfSet hs,
                bool applyCtf = true,
                bool applyTilt = true);

};

#endif
