data <- read.csv("par.csv")

data$r <- as.factor(data$r)

fit <- lm(y~., data = data)
summary(fit)

equation1 <- function(x){coef(fit)[2]*x+coef(fit)[1]}
equation2 <- function(x){coef(fit)[2]*x+coef(fit)[1]+coef(fit)[3]}
equation3 <- function(x){coef(fit)[2]*x+coef(fit)[1]+coef(fit)[4]}

library(ggplot2)

ggplot(data = data, mapping = aes(x=x, y=y, color= r)) +
  geom_point() +
  scale_color_manual(values=c("red", "blue", "yellow")) +
  labs(x = "Even Numbers", y = "Number of Partitions", color = "Mod 6") +
  stat_function(fun=equation1,geom="line",color="red") + 
  stat_function(fun=equation2,geom="line",color="blue") + 
  stat_function(fun=equation3,geom="line",color="yellow") +
  labs(x = "Even Numbers", y = "Number of Partitions", color = "Mod 6") + 
  ggtitle("The regression lines of number of Goldbach pairs between different congruence classes")
