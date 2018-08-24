PATH = "out/production/VoteProject/"
JAVAC = $(shell which javac)
JAVA = $(shell which java)
all:
	$(JAVAC) -d $(PATH) src/*.java
runserver:
	$(JAVA) -classpath $(PATH) VF
runclient:
	$(JAVA) -classpath $(PATH) VoterCli
clean:
	rm -rf out
