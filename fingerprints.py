import sys
import os
import numpy as np
from rdkit import Chem
from rdkit.Chem import rdFingerprintGenerator

def morgan_fp(sdf_file: str, out_npy: str, nbits:int=2048, radius:int=3):
    mfpgen = rdFingerprintGenerator.GetMorganGenerator(radius=radius,fpSize=nbits)
    suppl = Chem.SDMolSupplier(sdf_file)
    fps = list(mfpgen.GetFingerprint(m) for m in suppl if m is not None)
    npfps = np.array(fps).astype(np.uint8)
    np.save(out_npy, npfps)

if __name__ == '__main__':
    if len(sys.argv) != 5:
        print(f'Usage: {sys.argv[0]} <input sdf file> <output npy file> <Morgan FP radius> <Morgan FP bits>')
    sdf_path = sys.argv[1]
    npy = sys.argv[2]
    radius = int(sys.argv[3])
    nbits = int(sys.argv[4])
    morgan_fp(sdf_path, npy, nbits=nbits, radius=radius)
