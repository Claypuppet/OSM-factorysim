//
// Created by don on 30-5-18.
//

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../../src/visualizer/Event.h"
#include "../../src/visualizer/FileReader.h"

BOOST_AUTO_TEST_SUITE(Visualiser_File_Reader_Tests)

BOOST_AUTO_TEST_CASE(File_Reader_Events) {
  std::vector<visualisercore::EventPtr> events;

  file::FileReader reader;
  reader.deserializeEvents("/home/don/Downloads/Kleine_productiestraat.yaml", events);

  for(auto e : events)
  {
    std::cout << e->toString() << std::endl;
  }
}

BOOST_AUTO_TEST_SUITE_END()