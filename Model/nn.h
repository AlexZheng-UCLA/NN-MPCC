// Copyright 2022 Alex Zheng

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
#ifndef MPCC_NN_H
#define MPCC_NN_H

#include <torch/script.h>   // One-stop header.

#include <iostream>
#include <memory>

#include "config.h"
#include "types.h"
#include "Params/params.h"
#include "Model/model.h"

namespace mpcc{

class NN {
public:

    StateVector getF(const State &x,const Input &u);
    LinModelMatrix getLinModel(const State &x, const Input &u);
    std::vector<double> nnOutput(double vx, double vy, double r, double D, double delta);
    
    NN();
    NN(double Ts, const PathToJson &path);

private: 

    LinModelMatrix getModelJacobian(const State &x, const Input &u);
    LinModelMatrix discretizeModel(const LinModelMatrix &lin_model_c) const;
    std::vector<double> normalize(double vx, double vy, double r, double D, double delta) const;
    std::vector<double> denormalize(double dvx, double dvy, double dr) const;

    Param param_;
    const double Ts_;
    const int k_ = 1;  // The number of past states used 
    std::vector<std::vector<double>> input_record;
    torch::jit::Module module;

};




}


#endif //MPCC_NN_H

