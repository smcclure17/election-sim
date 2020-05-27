vote <-as.data.frame(voter_res)

library(usmap)
library(ggplot2)




#heatmap
plot_usmap(
  data = vote, values = "blue", color = "white", labels="TRUE", label_color = "white"
) + 
  scale_fill_continuous(
    low = "#ff0606", high = "#0606ff", name = "Vote Polarity", label = scales::comma
  ) + 
  labs(title = "Heatmap of Election Results (Political Percentage Method)", subtitle = "Red = % of red vote \nBlue = %of blue vote") +
  theme(legend.position = "right")

#basic plot
plot_usmap(
  data = vote, values = "result", labels="TRUE", label_color = "white", color = "white"
) + 
  scale_fill_manual(values = c("#0606ff", "#ff0606"))+ 
  labs(title = "Election Results by State (Political Percentage Method)", subtitle = "Red = red victory \nBlue = blue victory") +
  theme(legend.position = "right")

