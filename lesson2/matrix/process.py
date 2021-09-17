#!/usr/bin/env python3
import pandas as pd
import numpy as np

df = pd.read_csv('data.csv', index_col=0)
df.plot(grid=True, title='t-N figure').get_figure().savefig("../img/t-N.png", dpi=700)
dflog = df
dflog['my'] = np.log10(dflog['my'])
dflog['GEMM'] = np.log10(df['GEMM'])


dflog.plot(
    grid=True, title='log(t)-N figure').get_figure().savefig("../img/logt-N.png", dpi=700)
