import pandas as pd

df = pd.read_csv('data.csv', index_col=0)
df.plot(grid=True, title='t-N figure').get_figure().savefig("../../img/t-N.png", dpi=700)

# df['ratio'] = df['single_thread']/df['multi_thread']

# df1 = df['ratio']
# df1.plot(
#     grid=True, title='ratio-N figure').get_figure().savefig("../../img/ratio-N.png", dpi=700)
