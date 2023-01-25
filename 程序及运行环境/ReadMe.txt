关于持久化：
程序启动时读取在/data/data_load.txt的数据。
程序退出后会保存数据到/data/data_save.txt中。
为了让数据更新，请将load删掉并把save改成load。
此举防止意外退出，意外出库导致数据破坏。