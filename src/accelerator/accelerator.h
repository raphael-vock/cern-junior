#pragma once

#include "element.h"

class Accelerator{
	private:
		std::vector<Element*> element_list; // (ordered) list of elements that make up the accelerator
		std::vector<Particle*> particle_list; // list of particles
	public:
		Accelerator(std::vector<Element*> my_element_list = {}, std::vector<Particle*> my_particle_list = {}) : element_list(my_element_list), particle_list(my_particle_list){
			int N(element_list.size());
			try{
				for(int i(0); i <= N-2; ++i){
					element_list[i]->link(*element_list[i+1]);
				}
			}
			catch(...){ throw; }
		}
		std::ostream& print(std::ostream& output) const;

		void evolve(double dt);
};

std::ostream& operator<<(std::ostream& output, const Accelerator &A);
