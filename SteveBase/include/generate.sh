#!/bin/bash

function gen {
	rm index.hpp

	echo "#pragma once" >> index.hpp
	echo >> index.hpp

	for f in *.{hpp,h}; do 
		if [ $f != "index.hpp" ] && [ -e $f ]
		then
			echo "#include \"$f\"" >> index.hpp
		fi
	done
}

cd hook
gen

cd ../source_engine/def
gen

cd ../struct
gen

cd ../virtual
gen