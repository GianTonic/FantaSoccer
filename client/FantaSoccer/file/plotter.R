makePlot <- function (png_save_path= "plot.png") {
  a <- read.csv(file=file.path(".", "file.csv"), sep=";")
  # voglio un plot multiclasse (una per squadra), le giornate nelle x e i punti nelle y
  a$squad <- as.factor(a$squad)
  #pch=1:nlevels(a$squad)
  png(file.path(".", png_save_path))
  plot(x=a$day, y=a$point, col=a$squad, xlab="days", ylab="points", pch=1)
  legend("topright", pch=1, title="squads", legend=unique(a$squad), col=unique(a$squad))
  dev.off()
}

makePlot()

