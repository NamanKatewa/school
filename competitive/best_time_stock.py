class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        maxProfit = 0
        for x in range(0,len(prices)):
            for y in range(x+1,len(prices)):
                if prices[y] - prices[x] > maxProfit:
                    maxProfit = prices[y] - prices[x]
        return maxProfit