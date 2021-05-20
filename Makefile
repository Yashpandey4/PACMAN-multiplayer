.DEFAULT_GOAL := build

build: scripts/build.sh
	./$<

client: scripts/run.sh
	./$< client

server: scripts/run.sh
	./$< server

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r bin/debug"; $(RM) -r bin/debug

.PHONY: clean