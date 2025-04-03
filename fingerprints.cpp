#include "cnpy.h"
#include <GraphMol/GraphMol.h>
#include <GraphMol/FileParsers/MolSupplier.h>
#include <GraphMol/Fingerprints/MorganFingerprints.h>
#include <cstdlib>


int main(int argc, char* argv[])
{
    // const unsigned int radius = 3;
    // const unsigned int nbits = 2048;

    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <input sdf file> <output npy file> <Morgan FP radius> <Morgan FP bits>\n";
        return 1;
    }

    std::string sdf_file = argv[1];
    std::string npy_file = argv[2];
    unsigned int radius = atoi(argv[3]);
    unsigned int nbits = atoi(argv[4]);
    std::unique_ptr<RDKit::ROMol> mol;
    std::unique_ptr<ExplicitBitVect> fp;
    bool takeOwnership = true;
    RDKit::SDMolSupplier mol_supplier(sdf_file, takeOwnership);
    std::vector<std::vector<uint8_t>> data;
    while (!mol_supplier.atEnd()) {
        mol.reset(mol_supplier.next());
        if (!mol) {continue;}
        fp.reset(RDKit::MorganFingerprints::getFingerprintAsBitVect(*mol, radius, nbits));
        std::vector<uint8_t> v;
        for (int i=0; i<nbits; ++i) {
            v.push_back(fp->getBit(i));
        }
        data.push_back(v);
    }
    cnpy::npy_save(npy_file, &data[0][0], {data.size(), nbits}, "w");
    return 0;
}
