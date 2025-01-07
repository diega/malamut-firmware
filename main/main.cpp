#include <stdio.h>
#include <libsnark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>
#include <libsnark/gadgetlib1/protoboard.hpp>

extern "C" void app_main(void) {
    // Inicializar la curva
    libsnark::default_r1cs_ppzksnark_pp::init_public_params();
    
    // Crear dos elementos del campo finito
    libff::Fr<libsnark::default_r1cs_ppzksnark_pp> a = libff::Fr<libsnark::default_r1cs_ppzksnark_pp>::random_element();
    libff::Fr<libsnark::default_r1cs_ppzksnark_pp> b = libff::Fr<libsnark::default_r1cs_ppzksnark_pp>::random_element();
    
    // Multiplicarlos
    libff::Fr<libsnark::default_r1cs_ppzksnark_pp> c = a * b;

    printf("Operacion en el campo finito:\n");
    printf("a = "); a.print();
    printf("b = "); b.print();
    printf("a * b = "); c.print();
}