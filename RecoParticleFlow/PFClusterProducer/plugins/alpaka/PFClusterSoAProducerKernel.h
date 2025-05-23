#ifndef RecoParticleFlow_PFClusterProducer_PFClusterProducerAlpakaKernel_h
#define RecoParticleFlow_PFClusterProducer_PFClusterProducerAlpakaKernel_h

#include "DataFormats/ParticleFlowReco/interface/alpaka/PFClusterDeviceCollection.h"
#include "DataFormats/ParticleFlowReco/interface/alpaka/PFRecHitDeviceCollection.h"
#include "DataFormats/ParticleFlowReco/interface/alpaka/PFRecHitFractionDeviceCollection.h"
#include "HeterogeneousCore/AlpakaInterface/interface/config.h"
#include "RecoParticleFlow/PFClusterProducer/interface/alpaka/PFClusteringEdgeVarsDeviceCollection.h"
#include "RecoParticleFlow/PFClusterProducer/interface/alpaka/PFClusteringVarsDeviceCollection.h"
#include "RecoParticleFlow/PFRecHitProducer/interface/alpaka/PFRecHitTopologyDeviceCollection.h"

#include "PFClusterParamsSoA.h"

namespace ALPAKA_ACCELERATOR_NAMESPACE {

  namespace reco::pfClustering {
    struct Position4 {
      float x;
      float y;
      float z;
      float w;
    };

    struct Position3 {
      float x;
      float y;
      float z;
    };

    struct Neighbours4 {
      int x;
      int y;
      int z;
      int w;
    };
  }  // namespace reco::pfClustering

  class PFClusterProducerKernel {
  public:
    explicit PFClusterProducerKernel(Queue& queue);

    void seedTopoAndContract(Queue& queue,
                             const ::reco::PFClusterParamsSoA::ConstView params,
                             const reco::PFRecHitHCALTopologyDeviceCollection& topology,
                             reco::PFClusteringVarsDeviceCollection& pfClusteringVars,
                             reco::PFClusteringEdgeVarsDeviceCollection& pfClusteringEdgeVars,
                             const reco::PFRecHitDeviceCollection& pfRecHits,
                             int nRH,
                             reco::PFClusterDeviceCollection& pfClusters,
                             uint32_t* __restrict__ nRHF);

    void cluster(Queue& queue,
                 const ::reco::PFClusterParamsSoA::ConstView params,
                 const reco::PFRecHitHCALTopologyDeviceCollection& topology,
                 reco::PFClusteringVarsDeviceCollection& pfClusteringVars,
                 reco::PFClusteringEdgeVarsDeviceCollection& pfClusteringEdgeVars,
                 const reco::PFRecHitDeviceCollection& pfRecHits,
                 int nRH,
                 reco::PFClusterDeviceCollection& pfClusters,
                 reco::PFRecHitFractionDeviceCollection& pfrhFractions);

  private:
    cms::alpakatools::device_buffer<Device, uint32_t> nSeeds;
    cms::alpakatools::device_buffer<Device, reco::pfClustering::Position4[]> globalClusterPos;
    cms::alpakatools::device_buffer<Device, reco::pfClustering::Position4[]> globalPrevClusterPos;
    cms::alpakatools::device_buffer<Device, float[]> globalClusterEnergy;
    cms::alpakatools::device_buffer<Device, float[]> globalRhFracSum;
    cms::alpakatools::device_buffer<Device, int[]> globalSeeds;
    cms::alpakatools::device_buffer<Device, int[]> globalRechits;
  };

}  // namespace ALPAKA_ACCELERATOR_NAMESPACE

#endif
