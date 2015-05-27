all:
	  make -C src
		  cp -r src/output .

clean:
	  make clean -C src
		rm -rf output
