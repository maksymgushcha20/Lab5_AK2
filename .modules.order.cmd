cmd_/home/ubuntu20/SP_lab_work/Lab4/modules.order := {   echo /home/ubuntu20/SP_lab_work/Lab4/hello1.ko;   echo /home/ubuntu20/SP_lab_work/Lab4/hello2.ko; :; } | awk '!x[$$0]++' - > /home/ubuntu20/SP_lab_work/Lab4/modules.order