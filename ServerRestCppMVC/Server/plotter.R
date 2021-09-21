makePlot <- function (png_save_path= "plot.png") {
  a <- read.csv(file=file.path(".", "points.csv"), sep=";")
  a$squad <- as.factor(a$squad)
  #pch=1:nlevels(a$squad)
  png(file.path(".", png_save_path))
  plot(x=a$day, y=a$point, col=a$squad,xlim=c(0,max(a$day+1)), ylim=c(0,max(a$point+10)),cex = 1, xlab="days", ylab="points", pch=19)
  legend("topright", pch=19, title="squads", legend=unique(a$squad), col=unique(a$squad))
  dev.off()
}

makePlot()

