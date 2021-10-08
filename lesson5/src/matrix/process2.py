import pandas as pd

df = pd.read_csv('data.csv', index_col=0)

df['ratio_pthread'] = df['single']/df['pthread']
df['ratio_openmp'] = df['single']/df['openmp']
df = df.loc[:, ['ratio_pthread', 'ratio_openmp']]
df.plot(grid=True, title='ratio-N figure').get_figure().savefig("../../img/ratio-N.png", dpi=700)
