data <- read.csv("par.csv")

library(ggplot2)

ggplot(data = data, mapping = aes(x=x, y=y, color= factor(r))) + geom_point() + scale_color_manual(values=c("red", "blue", "yellow")) + labs(x = "Even Numbers", y = "Number of Partitions", color = "Mod 6") + ggtitle("The number of partitions varies between different congruence classes")

temp
