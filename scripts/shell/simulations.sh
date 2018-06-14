#!/bin/sh
cd ../../cmake-build-release/src/production_control/
./app_production_control configs/adviesrapport_configs/config_allesgoedkoop.yaml
./app_production_control configs/adviesrapport_configs/config_allesduur.yaml
./app_production_control configs/adviesrapport_configs/config_goedkopehogeproductie.yaml
./app_production_control configs/adviesrapport_configs/config_hogemtbfhogeproductie.yaml
./app_production_control configs/adviesrapport_configs/config_hoogstemtbf.yaml
./app_production_control configs/adviesrapport_configs/config_hoogsteproductie.yaml
echo Klaar is kees
