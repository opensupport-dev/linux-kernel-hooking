export APP_NAME = hello_world
export MOD_NAME = hooker

PWD := $(shell pwd)
APP_PATH=$(PWD)/d$(APP_NAME)
MOD_PAHT=$(PWD)/d$(MOD_NAME)

all: $(MOD_NAME) $(APP_NAME)

$(MOD_NAME):
	$(MAKE) -C $(MOD_PATH)
	mv $(MOD_PATH)/$@.ko $(PWD)

$(APP_NAME):
	$(MAKE) -C $(APP_PATH)
	mv $(APP_PATH)/$@ $(PWD)

clean:
	$(RM) $(PWD)/$(MOD_NAME).ko
	$(RM) $(PWD)/$(APP_NAME)
	arm-linux-gnueabihf-gcc -C $(MOD_PATH) clean
	arm-linux-gnueabihf-gcc -C $(APP_PATH) clean
