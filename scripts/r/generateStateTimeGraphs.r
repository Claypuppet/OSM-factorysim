library("rjson")

args = commandArgs(trailingOnly=TRUE)

if(length(args)==0){
	print("No arguments")
	close()
}

pdf(paste(args[2],".pdf"))

json_file <- args[1]
json_data <- fromJSON(file = json_file)

idleTimes = c()
productionTimes = c()
machineIds = c()
idleTimes = c()
configureTimes = c()
downTimes = c()
MTBFs = c()
totalProduced = c()
avgProduced = c()
totalLost = c()
avgLost = c()


i <- 1

finalStatistics = json_data["finalStatistics"][[1]]
machines = finalStatistics["machines"][[1]]

for(machine in machines){
	machineIds[i] <- machine["id"][[1]]
	productionTimes[i] <- machine["avgProductionTime"][[1]]
	idleTimes[i] <- machine["avgIdleTime"][[1]]
	downTimes[i] <- machine["avgDownTime"][[1]]
	configureTimes[i] <- machine["avgConfigureTime"][[1]]
	totalProduced <- machine["totalProducedProducts"][[1]]
	avgProduced <- machine["avgProducedProducts"][[1]]
	totalLost <- machine["totalLostProducts"][[1]]
	avgLost <- machine["avgLostProducts"][[1]]
	MTBFs[i] <- machine["MTBFinHours"][[1]]
	i <- i + 1
}

barplot(productionTimes, names.arg=machineIds, ylab="avg production time", xlab="machine id", col="blue", main="Average time spent in production")
barplot(idleTimes, names.arg=machineIds, ylab="avg idle time", xlab="machine id", col="blue", main="Average time spent in idle state")
barplot(downTimes, names.arg=machineIds, ylab="avg down time", xlab="machine id", col="blue", main="Average time spent broken")
barplot(configureTimes, names.arg=machineIds, ylab="avg configure time", xlab="machine id", col="blue", main="Average time spent configuring")
barplot(MTBFs, names.arg=machineIds, ylab="MTBF", xlab="machine id", col="blue", main="MTBF")

labels = c("Production", "Idle", "Broken", "Configuring");

for(i in 1:length(machineIds)){
	times = c()
	times[1] <- productionTimes[i]
	times[2] <- idleTimes[i]
	times[3] <- downTimes[i]
	times[4] <- configureTimes[i]
	chartName = sprintf("Machine %d" , machineIds[i])
	pie(times, labels, main=chartName)
}

#print(totalIdleTime)