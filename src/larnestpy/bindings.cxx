#include <pybind11/pybind11.h>
#include "LArNEST.h"
#include "Logger.h"
#include "RandomGen.h"
#include <pybind11/numpy.h>
#include <pybind11/stl_bind.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)
 
namespace py = pybind11;

PYBIND11_MODULE(larnestpy, m) 
{
	// versioning
#ifdef LARNESTPY_VERSION
    m.attr("__version__") = MACRO_STRINGIFY(LARNESTPY_VERSION);
#else
    m.attr("__version__") = "dev";
#endif
#ifdef LARNEST_VERSION
    m.attr("__larnest_version__") = MACRO_STRINGIFY(LARNEST_VERSION);
#else
    m.attr("__larnest_version__") = "";
#endif
	
	// Init random seed
	larnest::RandomGen::GetRandomGen()->SetSeed( time(nullptr) );
	// Binding for larnest::RandomGen class
	py::class_<larnest::RandomGen>(m, "RandomGen")
		.def("get_random_gen", &larnest::RandomGen::GetRandomGen)
		.def("set_seed", &larnest::RandomGen::SetSeed);

	//-----------------------------------------------------------------------
	// LAr NEST bindings

	//	Binding for the enumeration LArInteraction
	py::enum_<larnest::LArInteraction>(m, "LArInteraction", py::arithmetic())
		.value("NR", larnest::LArInteraction::NR)
		.value("ER", larnest::LArInteraction::ER)
		.value("Alpha", larnest::LArInteraction::Alpha)
		.export_values();

	// NR Yields Parameters
	py::class_<larnest::LArNRYieldsParameters>(m, "LArNRYieldsParameters", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("alpha", &larnest::LArNRYieldsParameters::alpha)
		.def_readwrite("beta", &larnest::LArNRYieldsParameters::beta)
		.def_readwrite("gamma", &larnest::LArNRYieldsParameters::gamma)
		.def_readwrite("delta", &larnest::LArNRYieldsParameters::delta)
		.def_readwrite("epsilon", &larnest::LArNRYieldsParameters::epsilon)
		.def_readwrite("zeta", &larnest::LArNRYieldsParameters::zeta)
		.def_readwrite("eta", &larnest::LArNRYieldsParameters::eta);
		
	// ER Electron Yields Alpha Parameters
	py::class_<larnest::LArERElectronYieldsAlphaParameters>(m, "LArERElectronYieldsAlphaParameters", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("A", &larnest::LArERElectronYieldsAlphaParameters::A)
		.def_readwrite("B", &larnest::LArERElectronYieldsAlphaParameters::B)
		.def_readwrite("C", &larnest::LArERElectronYieldsAlphaParameters::C)
		.def_readwrite("D", &larnest::LArERElectronYieldsAlphaParameters::D)
		.def_readwrite("E", &larnest::LArERElectronYieldsAlphaParameters::E)
		.def_readwrite("F", &larnest::LArERElectronYieldsAlphaParameters::F)
		.def_readwrite("G", &larnest::LArERElectronYieldsAlphaParameters::G);
	
	// ER Electron Yields Beta Parameters
	py::class_<larnest::LArERElectronYieldsBetaParameters>(m, "LArERElectronYieldsBetaParameters", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("A", &larnest::LArERElectronYieldsBetaParameters::A)
		.def_readwrite("B", &larnest::LArERElectronYieldsBetaParameters::B)
		.def_readwrite("C", &larnest::LArERElectronYieldsBetaParameters::C)
		.def_readwrite("D", &larnest::LArERElectronYieldsBetaParameters::D)
		.def_readwrite("E", &larnest::LArERElectronYieldsBetaParameters::E)
		.def_readwrite("F", &larnest::LArERElectronYieldsBetaParameters::F);

	// ER Electron Yields Gamma Parameters
	py::class_<larnest::LArERElectronYieldsGammaParameters>(m, "LArERElectronYieldsGammaParameters", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("A", &larnest::LArERElectronYieldsGammaParameters::A)
		.def_readwrite("B", &larnest::LArERElectronYieldsGammaParameters::B)
		.def_readwrite("C", &larnest::LArERElectronYieldsGammaParameters::C)
		.def_readwrite("D", &larnest::LArERElectronYieldsGammaParameters::D)
		.def_readwrite("E", &larnest::LArERElectronYieldsGammaParameters::E)
		.def_readwrite("F", &larnest::LArERElectronYieldsGammaParameters::F);
	
	// ER Electron Yields DokeBirks Parameters
	py::class_<larnest::LArERElectronYieldsDokeBirksParameters>(m, "LArERElectronYieldsDokeBirksParameters", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("A", &larnest::LArERElectronYieldsDokeBirksParameters::A)
		.def_readwrite("B", &larnest::LArERElectronYieldsDokeBirksParameters::B)
		.def_readwrite("C", &larnest::LArERElectronYieldsDokeBirksParameters::C)
		.def_readwrite("D", &larnest::LArERElectronYieldsDokeBirksParameters::D)
		.def_readwrite("E", &larnest::LArERElectronYieldsDokeBirksParameters::E);

	// ER Electron Yields Parameters
	py::class_<larnest::LArERYieldsParameters>(m, "LArERYieldsParameters", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("alpha", &larnest::LArERYieldsParameters::alpha)
		.def_readwrite("beta", &larnest::LArERYieldsParameters::beta)
		.def_readwrite("gamma", &larnest::LArERYieldsParameters::gamma)
		.def_readwrite("doke_birks", &larnest::LArERYieldsParameters::doke_birks)
		.def_readwrite("p1", &larnest::LArERYieldsParameters::p1)
		.def_readwrite("p2", &larnest::LArERYieldsParameters::p2)
		.def_readwrite("p3", &larnest::LArERYieldsParameters::p3)
		.def_readwrite("p4", &larnest::LArERYieldsParameters::p4)
		.def_readwrite("p5", &larnest::LArERYieldsParameters::p5)
		.def_readwrite("delta", &larnest::LArERYieldsParameters::delta)
		.def_readwrite("let", &larnest::LArERYieldsParameters::let);

	// Alpha Electron Yields Parameters
	py::class_<larnest::LArAlphaElectronYieldsParameters>(m, "LArAlphaElectronYieldsParameters", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("A", &larnest::LArAlphaElectronYieldsParameters::A)
		.def_readwrite("B", &larnest::LArAlphaElectronYieldsParameters::B)
		.def_readwrite("C", &larnest::LArAlphaElectronYieldsParameters::C)
		.def_readwrite("D", &larnest::LArAlphaElectronYieldsParameters::D)
		.def_readwrite("E", &larnest::LArAlphaElectronYieldsParameters::E)
		.def_readwrite("F", &larnest::LArAlphaElectronYieldsParameters::F)
		.def_readwrite("G", &larnest::LArAlphaElectronYieldsParameters::G)
		.def_readwrite("H", &larnest::LArAlphaElectronYieldsParameters::H)
		.def_readwrite("I", &larnest::LArAlphaElectronYieldsParameters::I)
		.def_readwrite("J", &larnest::LArAlphaElectronYieldsParameters::J);

	// Alpha Photon Yields Parameters
	py::class_<larnest::LArAlphaPhotonYieldsParameters>(m, "LArAlphaPhotonYieldsParameters", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("A", &larnest::LArAlphaPhotonYieldsParameters::A)
		.def_readwrite("B", &larnest::LArAlphaPhotonYieldsParameters::B)
		.def_readwrite("C", &larnest::LArAlphaPhotonYieldsParameters::C)
		.def_readwrite("D", &larnest::LArAlphaPhotonYieldsParameters::D)
		.def_readwrite("E", &larnest::LArAlphaPhotonYieldsParameters::E)
		.def_readwrite("F", &larnest::LArAlphaPhotonYieldsParameters::F)
		.def_readwrite("G", &larnest::LArAlphaPhotonYieldsParameters::G)
		.def_readwrite("H", &larnest::LArAlphaPhotonYieldsParameters::H)
		.def_readwrite("I", &larnest::LArAlphaPhotonYieldsParameters::I)
		.def_readwrite("J", &larnest::LArAlphaPhotonYieldsParameters::J)
		.def_readwrite("J", &larnest::LArAlphaPhotonYieldsParameters::K)
		.def_readwrite("J", &larnest::LArAlphaPhotonYieldsParameters::L)
		.def_readwrite("J", &larnest::LArAlphaPhotonYieldsParameters::M);

	// Alpha Yields Parameters
	py::class_<larnest::LArAlphaYieldsParameters>(m, "LArAlphaYieldsParameters", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("Ye", &larnest::LArAlphaYieldsParameters::Ye)
		.def_readwrite("Yph", &larnest::LArAlphaYieldsParameters::Yph);

	// Thomas-Imel Parameters
	py::class_<larnest::ThomasImelParameters>(m, "ThomasImelParameters", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("A", &larnest::ThomasImelParameters::A)
		.def_readwrite("B", &larnest::ThomasImelParameters::B);
	
	// Drift Parameters
	py::class_<larnest::DriftParameters>(m, "DriftParameters", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("A", &larnest::DriftParameters::A)
		.def_readwrite("B", &larnest::DriftParameters::B)
		.def_readwrite("C", &larnest::DriftParameters::B)
		.def_readwrite("TempLow", &larnest::DriftParameters::TempLow)
		.def_readwrite("TempHigh", &larnest::DriftParameters::TempHigh);

	// LAr Mean Yield Result
	py::class_<larnest::LArYieldResult>(m, "LArYieldResult", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("TotalYield", &larnest::LArYieldResult::TotalYield)
		.def_readwrite("QuantaYield", &larnest::LArYieldResult::QuantaYield)
		.def_readwrite("LightYield", &larnest::LArYieldResult::LightYield)
		.def_readwrite("Nph", &larnest::LArYieldResult::Nph)
		.def_readwrite("Ne", &larnest::LArYieldResult::Ne)
		.def_readwrite("Nex", &larnest::LArYieldResult::Nex)
		.def_readwrite("Nion", &larnest::LArYieldResult::Nion)
		.def_readwrite("Lindhard", &larnest::LArYieldResult::Lindhard)
		.def_readwrite("ElectricField", &larnest::LArYieldResult::ElectricField);

	// LAr Fluctuation Result
	py::class_<larnest::LArYieldFluctuationResult>(m, "LArYieldFluctuationResult", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("NphFluctuation", &larnest::LArYieldFluctuationResult::NphFluctuation)
		.def_readwrite("NeFluctuation", &larnest::LArYieldFluctuationResult::NeFluctuation)
		.def_readwrite("NexFluctuation", &larnest::LArYieldFluctuationResult::NexFluctuation)
		.def_readwrite("NionFluctuation", &larnest::LArYieldFluctuationResult::NionFluctuation);

	// LAr Yields Result
	py::class_<larnest::LArNESTResult>(m, "LArNESTResult", py::dynamic_attr())
		.def(py::init<>())
		.def_readwrite("yields", &larnest::LArNESTResult::yields)
		.def_readwrite("fluctuations", &larnest::LArNESTResult::fluctuations);
		//.def_readwrite("photon_times", &larnest::LArNESTResult::photon_times);

	//	Binding for the LArNEST class
	py::class_<larnest::LArNEST, std::unique_ptr<larnest::LArNEST, py::nodelete>>(m, "LArNEST")
		.def(py::init<>())
		.def("set_density", &larnest::LArNEST::SetDensity)
		.def("set_r_ideal_gas", &larnest::LArNEST::SetRIdealGas)
		.def("set_real_gas_a", &larnest::LArNEST::SetRealGasA)
		.def("set_real_gas_b", &larnest::LArNEST::SetRealGasB)
		.def("set_work_quanta_function", &larnest::LArNEST::SetWorkQuantaFunction)
		.def("set_work_ion_function", &larnest::LArNEST::SetWorkIonFunction)
		.def("set_work_photon_function", &larnest::LArNEST::SetWorkPhotonFunction)
		.def("set_fano_er", &larnest::LArNEST::SetFanoER)
		.def("set_nex_over_nion", &larnest::LArNEST::SetNexOverNion)
		//.def("get_density", &larnest::LArNEST::GetDensity)
		.def("get_r_ideal_gas", &larnest::LArNEST::GetRIdealGas)
		.def("get_real_gas_a", &larnest::LArNEST::GetRealGasA)
		.def("get_real_gas_b", &larnest::LArNEST::GetRealGasB)
		.def("get_work_quanta_function", &larnest::LArNEST::GetWorkQuantaFunction)
		.def("get_work_ion_function", &larnest::LArNEST::GetWorkIonFunction)
		.def("get_work_photon_function", &larnest::LArNEST::GetWorkPhotonFunction)
		.def("get_fano_er", &larnest::LArNEST::GetFanoER)
		.def("get_nex_over_nion", &larnest::LArNEST::GetNexOverNion)
		.def("get_nr_yields_parameters", &larnest::LArNEST::GetNRYieldsParameters)
		.def("get_er_yields_parameters", &larnest::LArNEST::GetERYieldsParameters)
		.def("get_er_electron_yields_alpha_parameters", &larnest::LArNEST::GetERElectronYieldsAlphaParameters)
		.def("get_er_electron_yields_beta_parameters", &larnest::LArNEST::GetERElectronYieldsBetaParameters)
		.def("get_er_electron_yields_gamma_parameters", &larnest::LArNEST::GetERElectronYieldsGammaParameters)
		.def("get_er_electron_yields_doke_birks_parameters", &larnest::LArNEST::GetERElectronYieldsDokeBirksParameters)
		.def("get_thomas_imel_parameters", &larnest::LArNEST::GetThomasImelParameters)
		.def("get_drift_parameters", &larnest::LArNEST::GetDriftParameters)

		.def("get_recombination_yields", &larnest::LArNEST::GetRecombinationYields)
		.def("get_yields", &larnest::LArNEST::GetYields)
		.def("get_yield_fluctuations", &larnest::LArNEST::GetYieldFluctuations)
		.def("full_calculation", &larnest::LArNEST::FullCalculation)
		.def("get_nr_total_yields", &larnest::LArNEST::GetNRTotalYields)
		.def("get_nr_electron_yields", &larnest::LArNEST::GetNRElectronYields)
		.def("get_nr_photon_yields", &larnest::LArNEST::GetNRPhotonYields)
		.def("get_nr_photon_yields_conserved", &larnest::LArNEST::GetNRPhotonYieldsConserved)
		.def("get_nr_yields", &larnest::LArNEST::GetNRYields)
		.def("get_er_total_yields", &larnest::LArNEST::GetERTotalYields)
		.def("get_er_electron_yields_alpha", &larnest::LArNEST::GetERElectronYieldsAlpha)
		.def("get_er_electron_yields_beta", &larnest::LArNEST::GetERElectronYieldsBeta)
		.def("get_er_electron_yields_gamma", &larnest::LArNEST::GetERElectronYieldsGamma)
		.def("get_er_electron_yields_doke_birks", &larnest::LArNEST::GetERElectronYieldsDokeBirks)
		.def("get_er_electron_yields", &larnest::LArNEST::GetERElectronYields)
		.def("get_er_yields", &larnest::LArNEST::GetERYields)
		.def("get_alpha_total_yields", &larnest::LArNEST::GetAlphaTotalYields)
		.def("get_alpha_electron_yields", &larnest::LArNEST::GetAlphaElectronYields)
		.def("get_alpha_photon_yields", &larnest::LArNEST::GetAlphaPhotonYields)
		.def("get_alpha_yields", &larnest::LArNEST::GetAlphaYields)

		//.def("get_default_fluctuations", &larnest::LArNEST::GetDefaultFluctuations)
		.def("get_photon_time", &larnest::LArNEST::GetPhotonTime)
		//.def("get_photon_energy", &larnest::LArNEST::GetPhotonEnergy)
		//.def("get_drift_velocity_liquid", &larnest::LArNEST::GetDriftVelocity_Liquid)
		//.def("get_drift_velocity_magboltz", &larnest::LArNEST::GetDriftVelocity_MagBoltz)
		//.def("get_let", &larnest::LArNEST::GetLinearEnergyTransfer)
		//.def("get_density", &larnest::LArNEST::GetDensity)
		//.def("calculate_g2", &larnest::LArNEST::CalculateG2)

		.def("legacy_get_yields", &larnest::LArNEST::LegacyGetYields)
		.def("legacy_calculation", &larnest::LArNEST::LegacyCalculation)
		.def("legacy_get_recombination_probability", &larnest::LArNEST::LegacyGetRecombinationProbability)
		.def("legacy_get_let", &larnest::LArNEST::LegacyGetLinearEnergyTransfer);

}
