---
title: Survival Report
---


{% capture template %}



<div class="section">
    <h1>Experiment Configuration</h1>
    <ul class="browser-default">
        <li><b>Duration</b>: 1w</li>
        <li><b>Trials</b>: 10</li>
        <li><b>Version</b>: v1.0</li>
    </ul>
</div>
<div class="section">
    <h1>Fuzz Targets</h1>
    <p>This report summarizes the results of fuzzing the following targets:</p>
    <ul id="target-list" class="browser-default">
        
        <li><a href="targets/libpng.html">libpng</a></li>
        
        <li><a href="targets/libtiff.html">libtiff</a></li>
        
        <li><a href="targets/libxml2.html">libxml2</a></li>
        
        <li><a href="targets/openssl.html">openssl</a></li>
        
        <li><a href="targets/php.html">php</a></li>
        
        <li><a href="targets/poppler.html">poppler</a></li>
        
        <li><a href="targets/sqlite3.html">sqlite3</a></li>
        
    </ul>
</div>

<div class="section">
    <h1>Evaluated Fuzzers</h1>
    <p>The fuzzers used in this evaluation are listed below:</p>
    <ul id="fuzzer-list" class="browser-default">
        
        <li><a href="fuzzers/afl.html">afl</a></li>
        
        <li><a href="fuzzers/aflfast.html">aflfast</a></li>
        
        <li><a href="fuzzers/aflplusplus.html">aflplusplus</a></li>
        
        <li><a href="fuzzers/honggfuzz.html">honggfuzz</a></li>
        
        <li><a href="fuzzers/moptafl.html">moptafl</a></li>
        
        <li><a href="fuzzers/symcc_afl.html">symcc_afl</a></li>
        
    </ul>
</div>

<!--
EXPERIMENT PARAMETERS WILL BE LISTED HERE
-->

<div class="section">
    <h1>Experiment Summary</h1>
    <div id="bugs-triggered">
        <h2>Total Unique Bugs Triggered</h2>
        <ul class="collapsible popout">
            <li>
                <div class="collapsible-header">
                    <h3>Mean and Standard Deviation</h3>
                </div>
                <div class="collapsible-body">
                    This plot shows the mean number of unique bugs triggered by every fuzzer against every target,
                    and the standard deviation bar, across all campaigns.
                </div>
            </li>
        </ul>
        <img class="materialboxed responsive-img" src="plot/summary_unique_bugs.svg">
        <ul class="collapsible popout">
            <li>
                <div class="collapsible-header">
                    <h3>Stastistical Significance</h3>
                </div>
                <div class="collapsible-body">
                    This matrix summarizes the p-values of the pairwise Mann-Whitney U tests calculated against the
                    total bug count sample sets collected for every fuzzer across all campaigns. Cells with a green
                    shade indicate that the number of bugs triggered by a fuzzer is statistically different.
                </div>
            </li>
        </ul>
        <img class="materialboxed responsive-img" src="plot/summary_signplot.svg">
    </div>

    <div id="mean-survival">
        <h2>Mean Survival Time</h2>
        <ul class="collapsible popout">
            <li>
                <div class="collapsible-header">
                    <h3>Ranking of Bugs and Fuzzers</h3>
                </div>
                <div class="collapsible-body">
                    This table shows the restricted mean survival time for every bug being reached or triggered over the
                    duration of the campaign, using the Kaplan-Meier non-parametric survival function estimator.
                    Green-shaded cells indicate the best performance (lowest time) for a bug metric across all fuzzers.
                    Yellow-shaded cells indicate the worst performance (highest time) for a bug metric across all fuzzers.
                    Red-shaded cells indicate that the bug survived being reached or triggered by the fuzzer throughout
                    the campaign duration.
                </div>
            </li>
        </ul>
        <div class="center">
            <a id="btn-colormap" class="btn-small waves-effect waves-light" style="margin-bottom: 10px; color: white; font-weight: normal;">
                <i class="material-icons left">color_lens</i>
                Change Colormap
            </a>
        </div>
        <script type="text/javascript">
            $('#btn-colormap').click(function() {
                stl = $('#survival_stylesheet')
                var href = stl.prop('href')
                if (href.includes('hiliter')) {
                    stl.prop('href', 'css/survival_heatmap.css');
                } else {
                    stl.prop('href', 'css/survival_hiliter.css');
                }
            });
        </script>
        <link id="survival_stylesheet" rel="stylesheet" href="css/survival_hiliter.css">
        <table id="T_survival_table" ><thead>    <tr>        <th class="index_name level0" >Fuzzer</th>        <th class="col_heading level0 col0" colspan="2">moptafl</th>        <th class="col_heading level0 col2" colspan="2">honggfuzz</th>        <th class="col_heading level0 col4" colspan="2">aflplusplus</th>        <th class="col_heading level0 col6" colspan="2">afl</th>        <th class="col_heading level0 col8" colspan="2">aflfast</th>        <th class="col_heading level0 col10" colspan="2">symcc_afl</th>    </tr>    <tr>        <th class="index_name level1" >Metric</th>        <th class="col_heading level1 col0" >R</th>        <th class="col_heading level1 col1" >T</th>        <th class="col_heading level1 col2" >R</th>        <th class="col_heading level1 col3" >T</th>        <th class="col_heading level1 col4" >R</th>        <th class="col_heading level1 col5" >T</th>        <th class="col_heading level1 col6" >R</th>        <th class="col_heading level1 col7" >T</th>        <th class="col_heading level1 col8" >R</th>        <th class="col_heading level1 col9" >T</th>        <th class="col_heading level1 col10" >R</th>        <th class="col_heading level1 col11" >T</th>    </tr>    <tr>        <th class="index_name level0" >Bug ID</th>        <th class="blank" ></th>        <th class="blank" ></th>        <th class="blank" ></th>        <th class="blank" ></th>        <th class="blank" ></th>        <th class="blank" ></th>        <th class="blank" ></th>        <th class="blank" ></th>        <th class="blank" ></th>        <th class="blank" ></th>        <th class="blank" ></th>        <th class="blank" ></th>    </tr></thead><tbody>
                <tr>
                        <th id="T_survival_tablelevel0_row0" class="row_heading level0 row0" >AAH037</th>
                        <td id="T_survival_tablerow0_col0" class="data row0 col0" >10s</td>
                        <td id="T_survival_tablerow0_col1" class="data row0 col1" >20s</td>
                        <td id="T_survival_tablerow0_col2" class="data row0 col2" >15s</td>
                        <td id="T_survival_tablerow0_col3" class="data row0 col3" >15s</td>
                        <td id="T_survival_tablerow0_col4" class="data row0 col4" >10s</td>
                        <td id="T_survival_tablerow0_col5" class="data row0 col5" >46s</td>
                        <td id="T_survival_tablerow0_col6" class="data row0 col6" >10s</td>
                        <td id="T_survival_tablerow0_col7" class="data row0 col7" >20s</td>
                        <td id="T_survival_tablerow0_col8" class="data row0 col8" >10s</td>
                        <td id="T_survival_tablerow0_col9" class="data row0 col9" >20s</td>
                        <td id="T_survival_tablerow0_col10" class="data row0 col10" >10s</td>
                        <td id="T_survival_tablerow0_col11" class="data row0 col11" >26s</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row1" class="row_heading level0 row1" >AAH041</th>
                        <td id="T_survival_tablerow1_col0" class="data row1 col0" >15s</td>
                        <td id="T_survival_tablerow1_col1" class="data row1 col1" >21s</td>
                        <td id="T_survival_tablerow1_col2" class="data row1 col2" >15s</td>
                        <td id="T_survival_tablerow1_col3" class="data row1 col3" >15s</td>
                        <td id="T_survival_tablerow1_col4" class="data row1 col4" >15s</td>
                        <td id="T_survival_tablerow1_col5" class="data row1 col5" >48s</td>
                        <td id="T_survival_tablerow1_col6" class="data row1 col6" >15s</td>
                        <td id="T_survival_tablerow1_col7" class="data row1 col7" >20s</td>
                        <td id="T_survival_tablerow1_col8" class="data row1 col8" >15s</td>
                        <td id="T_survival_tablerow1_col9" class="data row1 col9" >20s</td>
                        <td id="T_survival_tablerow1_col10" class="data row1 col10" >15s</td>
                        <td id="T_survival_tablerow1_col11" class="data row1 col11" >30s</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row2" class="row_heading level0 row2" >AAH003</th>
                        <td id="T_survival_tablerow2_col0" class="data row2 col0" >10s</td>
                        <td id="T_survival_tablerow2_col1" class="data row2 col1" >16s</td>
                        <td id="T_survival_tablerow2_col2" class="data row2 col2" >15s</td>
                        <td id="T_survival_tablerow2_col3" class="data row2 col3" >17s</td>
                        <td id="T_survival_tablerow2_col4" class="data row2 col4" >10s</td>
                        <td id="T_survival_tablerow2_col5" class="data row2 col5" >15s</td>
                        <td id="T_survival_tablerow2_col6" class="data row2 col6" >10s</td>
                        <td id="T_survival_tablerow2_col7" class="data row2 col7" >15s</td>
                        <td id="T_survival_tablerow2_col8" class="data row2 col8" >10s</td>
                        <td id="T_survival_tablerow2_col9" class="data row2 col9" >15s</td>
                        <td id="T_survival_tablerow2_col10" class="data row2 col10" >10s</td>
                        <td id="T_survival_tablerow2_col11" class="data row2 col11" >1m</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row3" class="row_heading level0 row3" >JCH207</th>
                        <td id="T_survival_tablerow3_col0" class="data row3 col0" >10s</td>
                        <td id="T_survival_tablerow3_col1" class="data row3 col1" >1m</td>
                        <td id="T_survival_tablerow3_col2" class="data row3 col2" >10s</td>
                        <td id="T_survival_tablerow3_col3" class="data row3 col3" >2m</td>
                        <td id="T_survival_tablerow3_col4" class="data row3 col4" >10s</td>
                        <td id="T_survival_tablerow3_col5" class="data row3 col5" >1m</td>
                        <td id="T_survival_tablerow3_col6" class="data row3 col6" >10s</td>
                        <td id="T_survival_tablerow3_col7" class="data row3 col7" >2m</td>
                        <td id="T_survival_tablerow3_col8" class="data row3 col8" >10s</td>
                        <td id="T_survival_tablerow3_col9" class="data row3 col9" >3m</td>
                        <td id="T_survival_tablerow3_col10" class="data row3 col10" >10s</td>
                        <td id="T_survival_tablerow3_col11" class="data row3 col11" >1m</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row4" class="row_heading level0 row4" >AAH056</th>
                        <td id="T_survival_tablerow4_col0" class="data row4 col0" >15s</td>
                        <td id="T_survival_tablerow4_col1" class="data row4 col1" >14m</td>
                        <td id="T_survival_tablerow4_col2" class="data row4 col2" >15s</td>
                        <td id="T_survival_tablerow4_col3" class="data row4 col3" >19m</td>
                        <td id="T_survival_tablerow4_col4" class="data row4 col4" >15s</td>
                        <td id="T_survival_tablerow4_col5" class="data row4 col5" >19m</td>
                        <td id="T_survival_tablerow4_col6" class="data row4 col6" >15s</td>
                        <td id="T_survival_tablerow4_col7" class="data row4 col7" >16m</td>
                        <td id="T_survival_tablerow4_col8" class="data row4 col8" >15s</td>
                        <td id="T_survival_tablerow4_col9" class="data row4 col9" >14m</td>
                        <td id="T_survival_tablerow4_col10" class="data row4 col10" >15s</td>
                        <td id="T_survival_tablerow4_col11" class="data row4 col11" >17m</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row5" class="row_heading level0 row5" >AAH015</th>
                        <td id="T_survival_tablerow5_col0" class="data row5 col0" >32s</td>
                        <td id="T_survival_tablerow5_col1" class="data row5 col1" >1m</td>
                        <td id="T_survival_tablerow5_col2" class="data row5 col2" >15s</td>
                        <td id="T_survival_tablerow5_col3" class="data row5 col3" >22s</td>
                        <td id="T_survival_tablerow5_col4" class="data row5 col4" >27s</td>
                        <td id="T_survival_tablerow5_col5" class="data row5 col5" >17m</td>
                        <td id="T_survival_tablerow5_col6" class="data row5 col6" >1m</td>
                        <td id="T_survival_tablerow5_col7" class="data row5 col7" >59m</td>
                        <td id="T_survival_tablerow5_col8" class="data row5 col8" >1m</td>
                        <td id="T_survival_tablerow5_col9" class="data row5 col9" >8m</td>
                        <td id="T_survival_tablerow5_col10" class="data row5 col10" >27m</td>
                        <td id="T_survival_tablerow5_col11" class="data row5 col11" >1h</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row6" class="row_heading level0 row6" >AAH052</th>
                        <td id="T_survival_tablerow6_col0" class="data row6 col0" >15s</td>
                        <td id="T_survival_tablerow6_col1" class="data row6 col1" >3m</td>
                        <td id="T_survival_tablerow6_col2" class="data row6 col2" >18s</td>
                        <td id="T_survival_tablerow6_col3" class="data row6 col3" >15m</td>
                        <td id="T_survival_tablerow6_col4" class="data row6 col4" >15s</td>
                        <td id="T_survival_tablerow6_col5" class="data row6 col5" >45m</td>
                        <td id="T_survival_tablerow6_col6" class="data row6 col6" >15s</td>
                        <td id="T_survival_tablerow6_col7" class="data row6 col7" >3h</td>
                        <td id="T_survival_tablerow6_col8" class="data row6 col8" >15s</td>
                        <td id="T_survival_tablerow6_col9" class="data row6 col9" >6h</td>
                        <td id="T_survival_tablerow6_col10" class="data row6 col10" >15s</td>
                        <td id="T_survival_tablerow6_col11" class="data row6 col11" >5m</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row7" class="row_heading level0 row7" >AAH055</th>
                        <td id="T_survival_tablerow7_col0" class="data row7 col0" >15s</td>
                        <td id="T_survival_tablerow7_col1" class="data row7 col1" >40m</td>
                        <td id="T_survival_tablerow7_col2" class="data row7 col2" >15s</td>
                        <td id="T_survival_tablerow7_col3" class="data row7 col3" >4m</td>
                        <td id="T_survival_tablerow7_col4" class="data row7 col4" >20s</td>
                        <td id="T_survival_tablerow7_col5" class="data row7 col5" >3h</td>
                        <td id="T_survival_tablerow7_col6" class="data row7 col6" >4m</td>
                        <td id="T_survival_tablerow7_col7" class="data row7 col7" >4h</td>
                        <td id="T_survival_tablerow7_col8" class="data row7 col8" >20s</td>
                        <td id="T_survival_tablerow7_col9" class="data row7 col9" >1h</td>
                        <td id="T_survival_tablerow7_col10" class="data row7 col10" >4m</td>
                        <td id="T_survival_tablerow7_col11" class="data row7 col11" >2h</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row8" class="row_heading level0 row8" >AAH020</th>
                        <td id="T_survival_tablerow8_col0" class="data row8 col0" >10s</td>
                        <td id="T_survival_tablerow8_col1" class="data row8 col1" >2h</td>
                        <td id="T_survival_tablerow8_col2" class="data row8 col2" >10s</td>
                        <td id="T_survival_tablerow8_col3" class="data row8 col3" >2h</td>
                        <td id="T_survival_tablerow8_col4" class="data row8 col4" >10s</td>
                        <td id="T_survival_tablerow8_col5" class="data row8 col5" >31m</td>
                        <td id="T_survival_tablerow8_col6" class="data row8 col6" >10s</td>
                        <td id="T_survival_tablerow8_col7" class="data row8 col7" >2h</td>
                        <td id="T_survival_tablerow8_col8" class="data row8 col8" >10s</td>
                        <td id="T_survival_tablerow8_col9" class="data row8 col9" >49m</td>
                        <td id="T_survival_tablerow8_col10" class="data row8 col10" >5s</td>
                        <td id="T_survival_tablerow8_col11" class="data row8 col11" >11h</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row9" class="row_heading level0 row9" >AAH022</th>
                        <td id="T_survival_tablerow9_col0" class="data row9 col0" >1m</td>
                        <td id="T_survival_tablerow9_col1" class="data row9 col1" >54m</td>
                        <td id="T_survival_tablerow9_col2" class="data row9 col2" >15s</td>
                        <td id="T_survival_tablerow9_col3" class="data row9 col3" >19m</td>
                        <td id="T_survival_tablerow9_col4" class="data row9 col4" >27s</td>
                        <td id="T_survival_tablerow9_col5" class="data row9 col5" >3h</td>
                        <td id="T_survival_tablerow9_col6" class="data row9 col6" >15m</td>
                        <td id="T_survival_tablerow9_col7" class="data row9 col7" >19h</td>
                        <td id="T_survival_tablerow9_col8" class="data row9 col8" >1m</td>
                        <td id="T_survival_tablerow9_col9" class="data row9 col9" >3h</td>
                        <td id="T_survival_tablerow9_col10" class="data row9 col10" >15m</td>
                        <td id="T_survival_tablerow9_col11" class="data row9 col11" >15h</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row10" class="row_heading level0 row10" >AAH032</th>
                        <td id="T_survival_tablerow10_col0" class="data row10 col0" >15s</td>
                        <td id="T_survival_tablerow10_col1" class="data row10 col1" >3m</td>
                        <td id="T_survival_tablerow10_col2" class="data row10 col2" >10s</td>
                        <td id="T_survival_tablerow10_col3" class="data row10 col3" >2m</td>
                        <td id="T_survival_tablerow10_col4" class="data row10 col4" >15s</td>
                        <td id="T_survival_tablerow10_col5" class="data row10 col5" >1h</td>
                        <td id="T_survival_tablerow10_col6" class="data row10 col6" >15s</td>
                        <td id="T_survival_tablerow10_col7" class="data row10 col7" >2d</td>
                        <td id="T_survival_tablerow10_col8" class="data row10 col8" >15s</td>
                        <td id="T_survival_tablerow10_col9" class="data row10 col9" >15m</td>
                        <td id="T_survival_tablerow10_col10" class="data row10 col10" >15s</td>
                        <td id="T_survival_tablerow10_col11" class="data row10 col11" >1d</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row11" class="row_heading level0 row11" >AAH017</th>
                        <td id="T_survival_tablerow11_col0" class="data row11 col0" >13h</td>
                        <td id="T_survival_tablerow11_col1" class="data row11 col1" >13h</td>
                        <td id="T_survival_tablerow11_col2" class="data row11 col2" >2d</td>
                        <td id="T_survival_tablerow11_col3" class="data row11 col3" >2d</td>
                        <td id="T_survival_tablerow11_col4" class="data row11 col4" >13h</td>
                        <td id="T_survival_tablerow11_col5" class="data row11 col5" >13h</td>
                        <td id="T_survival_tablerow11_col6" class="data row11 col6" >13h</td>
                        <td id="T_survival_tablerow11_col7" class="data row11 col7" >14h</td>
                        <td id="T_survival_tablerow11_col8" class="data row11 col8" >6h</td>
                        <td id="T_survival_tablerow11_col9" class="data row11 col9" >6h</td>
                        <td id="T_survival_tablerow11_col10" class="data row11 col10" >9h</td>
                        <td id="T_survival_tablerow11_col11" class="data row11 col11" >9h</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row12" class="row_heading level0 row12" >JCH215</th>
                        <td id="T_survival_tablerow12_col0" class="data row12 col0" >2m</td>
                        <td id="T_survival_tablerow12_col1" class="data row12 col1" >3h</td>
                        <td id="T_survival_tablerow12_col2" class="data row12 col2" >24s</td>
                        <td id="T_survival_tablerow12_col3" class="data row12 col3" >2h</td>
                        <td id="T_survival_tablerow12_col4" class="data row12 col4" >22m</td>
                        <td id="T_survival_tablerow12_col5" class="data row12 col5" >13h</td>
                        <td id="T_survival_tablerow12_col6" class="data row12 col6" >1h</td>
                        <td id="T_survival_tablerow12_col7" class="data row12 col7" >1d</td>
                        <td id="T_survival_tablerow12_col8" class="data row12 col8" >21m</td>
                        <td id="T_survival_tablerow12_col9" class="data row12 col9" >15h</td>
                        <td id="T_survival_tablerow12_col10" class="data row12 col10" >1h</td>
                        <td id="T_survival_tablerow12_col11" class="data row12 col11" >3d</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row13" class="row_heading level0 row13" >MAE016</th>
                        <td id="T_survival_tablerow13_col0" class="data row13 col0" >10s</td>
                        <td id="T_survival_tablerow13_col1" class="data row13 col1" >1m</td>
                        <td id="T_survival_tablerow13_col2" class="data row13 col2" >10s</td>
                        <td id="T_survival_tablerow13_col3" class="data row13 col3" >15s</td>
                        <td id="T_survival_tablerow13_col4" class="data row13 col4" >10s</td>
                        <td id="T_survival_tablerow13_col5" class="data row13 col5" >5m</td>
                        <td id="T_survival_tablerow13_col6" class="data row13 col6" >10s</td>
                        <td id="T_survival_tablerow13_col7" class="data row13 col7" >2m</td>
                        <td id="T_survival_tablerow13_col8" class="data row13 col8" >10s</td>
                        <td id="T_survival_tablerow13_col9" class="data row13 col9" >6m</td>
                        <td id="T_survival_tablerow13_col10" class="data row13 col10" >1w</td>
                        <td id="T_survival_tablerow13_col11" class="data row13 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row14" class="row_heading level0 row14" >MAE014</th>
                        <td id="T_survival_tablerow14_col0" class="data row14 col0" >15s</td>
                        <td id="T_survival_tablerow14_col1" class="data row14 col1" >1h</td>
                        <td id="T_survival_tablerow14_col2" class="data row14 col2" >15s</td>
                        <td id="T_survival_tablerow14_col3" class="data row14 col3" >55m</td>
                        <td id="T_survival_tablerow14_col4" class="data row14 col4" >15s</td>
                        <td id="T_survival_tablerow14_col5" class="data row14 col5" >14m</td>
                        <td id="T_survival_tablerow14_col6" class="data row14 col6" >15s</td>
                        <td id="T_survival_tablerow14_col7" class="data row14 col7" >4m</td>
                        <td id="T_survival_tablerow14_col8" class="data row14 col8" >15s</td>
                        <td id="T_survival_tablerow14_col9" class="data row14 col9" >10m</td>
                        <td id="T_survival_tablerow14_col10" class="data row14 col10" >1w</td>
                        <td id="T_survival_tablerow14_col11" class="data row14 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row15" class="row_heading level0 row15" >MAE008</th>
                        <td id="T_survival_tablerow15_col0" class="data row15 col0" >15s</td>
                        <td id="T_survival_tablerow15_col1" class="data row15 col1" >1h</td>
                        <td id="T_survival_tablerow15_col2" class="data row15 col2" >15s</td>
                        <td id="T_survival_tablerow15_col3" class="data row15 col3" >14h</td>
                        <td id="T_survival_tablerow15_col4" class="data row15 col4" >15s</td>
                        <td id="T_survival_tablerow15_col5" class="data row15 col5" >1m</td>
                        <td id="T_survival_tablerow15_col6" class="data row15 col6" >15s</td>
                        <td id="T_survival_tablerow15_col7" class="data row15 col7" >3m</td>
                        <td id="T_survival_tablerow15_col8" class="data row15 col8" >15s</td>
                        <td id="T_survival_tablerow15_col9" class="data row15 col9" >2m</td>
                        <td id="T_survival_tablerow15_col10" class="data row15 col10" >1w</td>
                        <td id="T_survival_tablerow15_col11" class="data row15 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row16" class="row_heading level0 row16" >JCH201</th>
                        <td id="T_survival_tablerow16_col0" class="data row16 col0" >15s</td>
                        <td id="T_survival_tablerow16_col1" class="data row16 col1" >17h</td>
                        <td id="T_survival_tablerow16_col2" class="data row16 col2" >15s</td>
                        <td id="T_survival_tablerow16_col3" class="data row16 col3" >5d</td>
                        <td id="T_survival_tablerow16_col4" class="data row16 col4" >15s</td>
                        <td id="T_survival_tablerow16_col5" class="data row16 col5" >20h</td>
                        <td id="T_survival_tablerow16_col6" class="data row16 col6" >15s</td>
                        <td id="T_survival_tablerow16_col7" class="data row16 col7" >11h</td>
                        <td id="T_survival_tablerow16_col8" class="data row16 col8" >15s</td>
                        <td id="T_survival_tablerow16_col9" class="data row16 col9" >13h</td>
                        <td id="T_survival_tablerow16_col10" class="data row16 col10" >15s</td>
                        <td id="T_survival_tablerow16_col11" class="data row16 col11" >14h</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row17" class="row_heading level0 row17" >JCH232</th>
                        <td id="T_survival_tablerow17_col0" class="data row17 col0" >4h</td>
                        <td id="T_survival_tablerow17_col1" class="data row17 col1" >4h</td>
                        <td id="T_survival_tablerow17_col2" class="data row17 col2" >44m</td>
                        <td id="T_survival_tablerow17_col3" class="data row17 col3" >2h</td>
                        <td id="T_survival_tablerow17_col4" class="data row17 col4" >1d</td>
                        <td id="T_survival_tablerow17_col5" class="data row17 col5" >2d</td>
                        <td id="T_survival_tablerow17_col6" class="data row17 col6" >3d</td>
                        <td id="T_survival_tablerow17_col7" class="data row17 col7" >4d</td>
                        <td id="T_survival_tablerow17_col8" class="data row17 col8" >1d</td>
                        <td id="T_survival_tablerow17_col9" class="data row17 col9" >2d</td>
                        <td id="T_survival_tablerow17_col10" class="data row17 col10" >4d</td>
                        <td id="T_survival_tablerow17_col11" class="data row17 col11" >4d</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row18" class="row_heading level0 row18" >AAH014</th>
                        <td id="T_survival_tablerow18_col0" class="data row18 col0" >14h</td>
                        <td id="T_survival_tablerow18_col1" class="data row18 col1" >14h</td>
                        <td id="T_survival_tablerow18_col2" class="data row18 col2" >5d</td>
                        <td id="T_survival_tablerow18_col3" class="data row18 col3" >5d</td>
                        <td id="T_survival_tablerow18_col4" class="data row18 col4" >13h</td>
                        <td id="T_survival_tablerow18_col5" class="data row18 col5" >13h</td>
                        <td id="T_survival_tablerow18_col6" class="data row18 col6" >18h</td>
                        <td id="T_survival_tablerow18_col7" class="data row18 col7" >18h</td>
                        <td id="T_survival_tablerow18_col8" class="data row18 col8" >5d</td>
                        <td id="T_survival_tablerow18_col9" class="data row18 col9" >5d</td>
                        <td id="T_survival_tablerow18_col10" class="data row18 col10" >1d</td>
                        <td id="T_survival_tablerow18_col11" class="data row18 col11" >1d</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row19" class="row_heading level0 row19" >AAH008</th>
                        <td id="T_survival_tablerow19_col0" class="data row19 col0" >15s</td>
                        <td id="T_survival_tablerow19_col1" class="data row19 col1" >1d</td>
                        <td id="T_survival_tablerow19_col2" class="data row19 col2" >15s</td>
                        <td id="T_survival_tablerow19_col3" class="data row19 col3" >3h</td>
                        <td id="T_survival_tablerow19_col4" class="data row19 col4" >15s</td>
                        <td id="T_survival_tablerow19_col5" class="data row19 col5" >5d</td>
                        <td id="T_survival_tablerow19_col6" class="data row19 col6" >15s</td>
                        <td id="T_survival_tablerow19_col7" class="data row19 col7" >1d</td>
                        <td id="T_survival_tablerow19_col8" class="data row19 col8" >15s</td>
                        <td id="T_survival_tablerow19_col9" class="data row19 col9" >5d</td>
                        <td id="T_survival_tablerow19_col10" class="data row19 col10" >15s</td>
                        <td id="T_survival_tablerow19_col11" class="data row19 col11" >2d</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row20" class="row_heading level0 row20" >JCH209</th>
                        <td id="T_survival_tablerow20_col0" class="data row20 col0" >14m</td>
                        <td id="T_survival_tablerow20_col1" class="data row20 col1" >14m</td>
                        <td id="T_survival_tablerow20_col2" class="data row20 col2" >1w</td>
                        <td id="T_survival_tablerow20_col3" class="data row20 col3" >1w</td>
                        <td id="T_survival_tablerow20_col4" class="data row20 col4" >2d</td>
                        <td id="T_survival_tablerow20_col5" class="data row20 col5" >2d</td>
                        <td id="T_survival_tablerow20_col6" class="data row20 col6" >2d</td>
                        <td id="T_survival_tablerow20_col7" class="data row20 col7" >2d</td>
                        <td id="T_survival_tablerow20_col8" class="data row20 col8" >1d</td>
                        <td id="T_survival_tablerow20_col9" class="data row20 col9" >1d</td>
                        <td id="T_survival_tablerow20_col10" class="data row20 col10" >2d</td>
                        <td id="T_survival_tablerow20_col11" class="data row20 col11" >2d</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row21" class="row_heading level0 row21" >MAE115</th>
                        <td id="T_survival_tablerow21_col0" class="data row21 col0" >15s</td>
                        <td id="T_survival_tablerow21_col1" class="data row21 col1" >2d</td>
                        <td id="T_survival_tablerow21_col2" class="data row21 col2" >15s</td>
                        <td id="T_survival_tablerow21_col3" class="data row21 col3" >4d</td>
                        <td id="T_survival_tablerow21_col4" class="data row21 col4" >15s</td>
                        <td id="T_survival_tablerow21_col5" class="data row21 col5" >5d</td>
                        <td id="T_survival_tablerow21_col6" class="data row21 col6" >15s</td>
                        <td id="T_survival_tablerow21_col7" class="data row21 col7" >1d</td>
                        <td id="T_survival_tablerow21_col8" class="data row21 col8" >15s</td>
                        <td id="T_survival_tablerow21_col9" class="data row21 col9" >1d</td>
                        <td id="T_survival_tablerow21_col10" class="data row21 col10" >15s</td>
                        <td id="T_survival_tablerow21_col11" class="data row21 col11" >10h</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row22" class="row_heading level0 row22" >AAH010</th>
                        <td id="T_survival_tablerow22_col0" class="data row22 col0" >1d</td>
                        <td id="T_survival_tablerow22_col1" class="data row22 col1" >1d</td>
                        <td id="T_survival_tablerow22_col2" class="data row22 col2" >22h</td>
                        <td id="T_survival_tablerow22_col3" class="data row22 col3" >1d</td>
                        <td id="T_survival_tablerow22_col4" class="data row22 col4" >14m</td>
                        <td id="T_survival_tablerow22_col5" class="data row22 col5" >5d</td>
                        <td id="T_survival_tablerow22_col6" class="data row22 col6" >14m</td>
                        <td id="T_survival_tablerow22_col7" class="data row22 col7" >1w</td>
                        <td id="T_survival_tablerow22_col8" class="data row22 col8" >5d</td>
                        <td id="T_survival_tablerow22_col9" class="data row22 col9" >6d</td>
                        <td id="T_survival_tablerow22_col10" class="data row22 col10" >19h</td>
                        <td id="T_survival_tablerow22_col11" class="data row22 col11" >2d</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row23" class="row_heading level0 row23" >JCH228</th>
                        <td id="T_survival_tablerow23_col0" class="data row23 col0" >16h</td>
                        <td id="T_survival_tablerow23_col1" class="data row23 col1" >1d</td>
                        <td id="T_survival_tablerow23_col2" class="data row23 col2" >6h</td>
                        <td id="T_survival_tablerow23_col3" class="data row23 col3" >2d</td>
                        <td id="T_survival_tablerow23_col4" class="data row23 col4" >3d</td>
                        <td id="T_survival_tablerow23_col5" class="data row23 col5" >4d</td>
                        <td id="T_survival_tablerow23_col6" class="data row23 col6" >5d</td>
                        <td id="T_survival_tablerow23_col7" class="data row23 col7" >6d</td>
                        <td id="T_survival_tablerow23_col8" class="data row23 col8" >2d</td>
                        <td id="T_survival_tablerow23_col9" class="data row23 col9" >4d</td>
                        <td id="T_survival_tablerow23_col10" class="data row23 col10" >5d</td>
                        <td id="T_survival_tablerow23_col11" class="data row23 col11" >6d</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row24" class="row_heading level0 row24" >AAH007</th>
                        <td id="T_survival_tablerow24_col0" class="data row24 col0" >15s</td>
                        <td id="T_survival_tablerow24_col1" class="data row24 col1" >1w</td>
                        <td id="T_survival_tablerow24_col2" class="data row24 col2" >10s</td>
                        <td id="T_survival_tablerow24_col3" class="data row24 col3" >1m</td>
                        <td id="T_survival_tablerow24_col4" class="data row24 col4" >15s</td>
                        <td id="T_survival_tablerow24_col5" class="data row24 col5" >6d</td>
                        <td id="T_survival_tablerow24_col6" class="data row24 col6" >15s</td>
                        <td id="T_survival_tablerow24_col7" class="data row24 col7" >6d</td>
                        <td id="T_survival_tablerow24_col8" class="data row24 col8" >15s</td>
                        <td id="T_survival_tablerow24_col9" class="data row24 col9" >1w</td>
                        <td id="T_survival_tablerow24_col10" class="data row24 col10" >15s</td>
                        <td id="T_survival_tablerow24_col11" class="data row24 col11" >23m</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row25" class="row_heading level0 row25" >AAH045</th>
                        <td id="T_survival_tablerow25_col0" class="data row25 col0" >20s</td>
                        <td id="T_survival_tablerow25_col1" class="data row25 col1" >3h</td>
                        <td id="T_survival_tablerow25_col2" class="data row25 col2" >20s</td>
                        <td id="T_survival_tablerow25_col3" class="data row25 col3" >21m</td>
                        <td id="T_survival_tablerow25_col4" class="data row25 col4" >20s</td>
                        <td id="T_survival_tablerow25_col5" class="data row25 col5" >1w</td>
                        <td id="T_survival_tablerow25_col6" class="data row25 col6" >20s</td>
                        <td id="T_survival_tablerow25_col7" class="data row25 col7" >1w</td>
                        <td id="T_survival_tablerow25_col8" class="data row25 col8" >20s</td>
                        <td id="T_survival_tablerow25_col9" class="data row25 col9" >6d</td>
                        <td id="T_survival_tablerow25_col10" class="data row25 col10" >20s</td>
                        <td id="T_survival_tablerow25_col11" class="data row25 col11" >6d</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row26" class="row_heading level0 row26" >MAE104</th>
                        <td id="T_survival_tablerow26_col0" class="data row26 col0" >15s</td>
                        <td id="T_survival_tablerow26_col1" class="data row26 col1" >2d</td>
                        <td id="T_survival_tablerow26_col2" class="data row26 col2" >15s</td>
                        <td id="T_survival_tablerow26_col3" class="data row26 col3" >1w</td>
                        <td id="T_survival_tablerow26_col4" class="data row26 col4" >15s</td>
                        <td id="T_survival_tablerow26_col5" class="data row26 col5" >4d</td>
                        <td id="T_survival_tablerow26_col6" class="data row26 col6" >15s</td>
                        <td id="T_survival_tablerow26_col7" class="data row26 col7" >4d</td>
                        <td id="T_survival_tablerow26_col8" class="data row26 col8" >15s</td>
                        <td id="T_survival_tablerow26_col9" class="data row26 col9" >2d</td>
                        <td id="T_survival_tablerow26_col10" class="data row26 col10" >1w</td>
                        <td id="T_survival_tablerow26_col11" class="data row26 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row27" class="row_heading level0 row27" >AAH013</th>
                        <td id="T_survival_tablerow27_col0" class="data row27 col0" >1w</td>
                        <td id="T_survival_tablerow27_col1" class="data row27 col1" >1w</td>
                        <td id="T_survival_tablerow27_col2" class="data row27 col2" >2h</td>
                        <td id="T_survival_tablerow27_col3" class="data row27 col3" >2h</td>
                        <td id="T_survival_tablerow27_col4" class="data row27 col4" >13h</td>
                        <td id="T_survival_tablerow27_col5" class="data row27 col5" >13h</td>
                        <td id="T_survival_tablerow27_col6" class="data row27 col6" >1w</td>
                        <td id="T_survival_tablerow27_col7" class="data row27 col7" >1w</td>
                        <td id="T_survival_tablerow27_col8" class="data row27 col8" >1w</td>
                        <td id="T_survival_tablerow27_col9" class="data row27 col9" >1w</td>
                        <td id="T_survival_tablerow27_col10" class="data row27 col10" >1w</td>
                        <td id="T_survival_tablerow27_col11" class="data row27 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row28" class="row_heading level0 row28" >AAH001</th>
                        <td id="T_survival_tablerow28_col0" class="data row28 col0" >15s</td>
                        <td id="T_survival_tablerow28_col1" class="data row28 col1" >6d</td>
                        <td id="T_survival_tablerow28_col2" class="data row28 col2" >15s</td>
                        <td id="T_survival_tablerow28_col3" class="data row28 col3" >12h</td>
                        <td id="T_survival_tablerow28_col4" class="data row28 col4" >15s</td>
                        <td id="T_survival_tablerow28_col5" class="data row28 col5" >1w</td>
                        <td id="T_survival_tablerow28_col6" class="data row28 col6" >15s</td>
                        <td id="T_survival_tablerow28_col7" class="data row28 col7" >6d</td>
                        <td id="T_survival_tablerow28_col8" class="data row28 col8" >15s</td>
                        <td id="T_survival_tablerow28_col9" class="data row28 col9" >1w</td>
                        <td id="T_survival_tablerow28_col10" class="data row28 col10" >15s</td>
                        <td id="T_survival_tablerow28_col11" class="data row28 col11" >3d</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row29" class="row_heading level0 row29" >AAH024</th>
                        <td id="T_survival_tablerow29_col0" class="data row29 col0" >15s</td>
                        <td id="T_survival_tablerow29_col1" class="data row29 col1" >9h</td>
                        <td id="T_survival_tablerow29_col2" class="data row29 col2" >20s</td>
                        <td id="T_survival_tablerow29_col3" class="data row29 col3" >2d</td>
                        <td id="T_survival_tablerow29_col4" class="data row29 col4" >15s</td>
                        <td id="T_survival_tablerow29_col5" class="data row29 col5" >1w</td>
                        <td id="T_survival_tablerow29_col6" class="data row29 col6" >15s</td>
                        <td id="T_survival_tablerow29_col7" class="data row29 col7" >1w</td>
                        <td id="T_survival_tablerow29_col8" class="data row29 col8" >15s</td>
                        <td id="T_survival_tablerow29_col9" class="data row29 col9" >1w</td>
                        <td id="T_survival_tablerow29_col10" class="data row29 col10" >15s</td>
                        <td id="T_survival_tablerow29_col11" class="data row29 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row30" class="row_heading level0 row30" >AAH016</th>
                        <td id="T_survival_tablerow30_col0" class="data row30 col0" >2d</td>
                        <td id="T_survival_tablerow30_col1" class="data row30 col1" >2d</td>
                        <td id="T_survival_tablerow30_col2" class="data row30 col2" >5d</td>
                        <td id="T_survival_tablerow30_col3" class="data row30 col3" >5d</td>
                        <td id="T_survival_tablerow30_col4" class="data row30 col4" >5d</td>
                        <td id="T_survival_tablerow30_col5" class="data row30 col5" >5d</td>
                        <td id="T_survival_tablerow30_col6" class="data row30 col6" >3d</td>
                        <td id="T_survival_tablerow30_col7" class="data row30 col7" >6d</td>
                        <td id="T_survival_tablerow30_col8" class="data row30 col8" >4d</td>
                        <td id="T_survival_tablerow30_col9" class="data row30 col9" >5d</td>
                        <td id="T_survival_tablerow30_col10" class="data row30 col10" >6d</td>
                        <td id="T_survival_tablerow30_col11" class="data row30 col11" >6d</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row31" class="row_heading level0 row31" >AAH026</th>
                        <td id="T_survival_tablerow31_col0" class="data row31 col0" >15s</td>
                        <td id="T_survival_tablerow31_col1" class="data row31 col1" >3d</td>
                        <td id="T_survival_tablerow31_col2" class="data row31 col2" >15s</td>
                        <td id="T_survival_tablerow31_col3" class="data row31 col3" >15h</td>
                        <td id="T_survival_tablerow31_col4" class="data row31 col4" >15s</td>
                        <td id="T_survival_tablerow31_col5" class="data row31 col5" >1w</td>
                        <td id="T_survival_tablerow31_col6" class="data row31 col6" >15s</td>
                        <td id="T_survival_tablerow31_col7" class="data row31 col7" >1w</td>
                        <td id="T_survival_tablerow31_col8" class="data row31 col8" >15s</td>
                        <td id="T_survival_tablerow31_col9" class="data row31 col9" >1w</td>
                        <td id="T_survival_tablerow31_col10" class="data row31 col10" >15s</td>
                        <td id="T_survival_tablerow31_col11" class="data row31 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row32" class="row_heading level0 row32" >JCH226</th>
                        <td id="T_survival_tablerow32_col0" class="data row32 col0" >2d</td>
                        <td id="T_survival_tablerow32_col1" class="data row32 col1" >3d</td>
                        <td id="T_survival_tablerow32_col2" class="data row32 col2" >3h</td>
                        <td id="T_survival_tablerow32_col3" class="data row32 col3" >19h</td>
                        <td id="T_survival_tablerow32_col4" class="data row32 col4" >1w</td>
                        <td id="T_survival_tablerow32_col5" class="data row32 col5" >1w</td>
                        <td id="T_survival_tablerow32_col6" class="data row32 col6" >1w</td>
                        <td id="T_survival_tablerow32_col7" class="data row32 col7" >1w</td>
                        <td id="T_survival_tablerow32_col8" class="data row32 col8" >1w</td>
                        <td id="T_survival_tablerow32_col9" class="data row32 col9" >1w</td>
                        <td id="T_survival_tablerow32_col10" class="data row32 col10" >1w</td>
                        <td id="T_survival_tablerow32_col11" class="data row32 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row33" class="row_heading level0 row33" >AAH049</th>
                        <td id="T_survival_tablerow33_col0" class="data row33 col0" >20s</td>
                        <td id="T_survival_tablerow33_col1" class="data row33 col1" >1d</td>
                        <td id="T_survival_tablerow33_col2" class="data row33 col2" >15s</td>
                        <td id="T_survival_tablerow33_col3" class="data row33 col3" >1w</td>
                        <td id="T_survival_tablerow33_col4" class="data row33 col4" >15s</td>
                        <td id="T_survival_tablerow33_col5" class="data row33 col5" >1w</td>
                        <td id="T_survival_tablerow33_col6" class="data row33 col6" >15s</td>
                        <td id="T_survival_tablerow33_col7" class="data row33 col7" >1w</td>
                        <td id="T_survival_tablerow33_col8" class="data row33 col8" >15s</td>
                        <td id="T_survival_tablerow33_col9" class="data row33 col9" >1w</td>
                        <td id="T_survival_tablerow33_col10" class="data row33 col10" >15s</td>
                        <td id="T_survival_tablerow33_col11" class="data row33 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row34" class="row_heading level0 row34" >JCH210</th>
                        <td id="T_survival_tablerow34_col0" class="data row34 col0" >30s</td>
                        <td id="T_survival_tablerow34_col1" class="data row34 col1" >2d</td>
                        <td id="T_survival_tablerow34_col2" class="data row34 col2" >34s</td>
                        <td id="T_survival_tablerow34_col3" class="data row34 col3" >6d</td>
                        <td id="T_survival_tablerow34_col4" class="data row34 col4" >1m</td>
                        <td id="T_survival_tablerow34_col5" class="data row34 col5" >1w</td>
                        <td id="T_survival_tablerow34_col6" class="data row34 col6" >1m</td>
                        <td id="T_survival_tablerow34_col7" class="data row34 col7" >1w</td>
                        <td id="T_survival_tablerow34_col8" class="data row34 col8" >1m</td>
                        <td id="T_survival_tablerow34_col9" class="data row34 col9" >1w</td>
                        <td id="T_survival_tablerow34_col10" class="data row34 col10" >1m</td>
                        <td id="T_survival_tablerow34_col11" class="data row34 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row35" class="row_heading level0 row35" >AAH035</th>
                        <td id="T_survival_tablerow35_col0" class="data row35 col0" >15s</td>
                        <td id="T_survival_tablerow35_col1" class="data row35 col1" >3d</td>
                        <td id="T_survival_tablerow35_col2" class="data row35 col2" >15s</td>
                        <td id="T_survival_tablerow35_col3" class="data row35 col3" >1w</td>
                        <td id="T_survival_tablerow35_col4" class="data row35 col4" >25s</td>
                        <td id="T_survival_tablerow35_col5" class="data row35 col5" >1w</td>
                        <td id="T_survival_tablerow35_col6" class="data row35 col6" >15s</td>
                        <td id="T_survival_tablerow35_col7" class="data row35 col7" >1w</td>
                        <td id="T_survival_tablerow35_col8" class="data row35 col8" >15s</td>
                        <td id="T_survival_tablerow35_col9" class="data row35 col9" >1w</td>
                        <td id="T_survival_tablerow35_col10" class="data row35 col10" >20s</td>
                        <td id="T_survival_tablerow35_col11" class="data row35 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row36" class="row_heading level0 row36" >JCH212</th>
                        <td id="T_survival_tablerow36_col0" class="data row36 col0" >15s</td>
                        <td id="T_survival_tablerow36_col1" class="data row36 col1" >1w</td>
                        <td id="T_survival_tablerow36_col2" class="data row36 col2" >20s</td>
                        <td id="T_survival_tablerow36_col3" class="data row36 col3" >3d</td>
                        <td id="T_survival_tablerow36_col4" class="data row36 col4" >15s</td>
                        <td id="T_survival_tablerow36_col5" class="data row36 col5" >1w</td>
                        <td id="T_survival_tablerow36_col6" class="data row36 col6" >15s</td>
                        <td id="T_survival_tablerow36_col7" class="data row36 col7" >1w</td>
                        <td id="T_survival_tablerow36_col8" class="data row36 col8" >15s</td>
                        <td id="T_survival_tablerow36_col9" class="data row36 col9" >1w</td>
                        <td id="T_survival_tablerow36_col10" class="data row36 col10" >15s</td>
                        <td id="T_survival_tablerow36_col11" class="data row36 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row37" class="row_heading level0 row37" >JCH227</th>
                        <td id="T_survival_tablerow37_col0" class="data row37 col0" >2d</td>
                        <td id="T_survival_tablerow37_col1" class="data row37 col1" >5d</td>
                        <td id="T_survival_tablerow37_col2" class="data row37 col2" >4d</td>
                        <td id="T_survival_tablerow37_col3" class="data row37 col3" >6d</td>
                        <td id="T_survival_tablerow37_col4" class="data row37 col4" >1w</td>
                        <td id="T_survival_tablerow37_col5" class="data row37 col5" >1w</td>
                        <td id="T_survival_tablerow37_col6" class="data row37 col6" >1w</td>
                        <td id="T_survival_tablerow37_col7" class="data row37 col7" >1w</td>
                        <td id="T_survival_tablerow37_col8" class="data row37 col8" >1w</td>
                        <td id="T_survival_tablerow37_col9" class="data row37 col9" >1w</td>
                        <td id="T_survival_tablerow37_col10" class="data row37 col10" >1w</td>
                        <td id="T_survival_tablerow37_col11" class="data row37 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row38" class="row_heading level0 row38" >AAH025</th>
                        <td id="T_survival_tablerow38_col0" class="data row38 col0" >5d</td>
                        <td id="T_survival_tablerow38_col1" class="data row38 col1" >5d</td>
                        <td id="T_survival_tablerow38_col2" class="data row38 col2" >6d</td>
                        <td id="T_survival_tablerow38_col3" class="data row38 col3" >6d</td>
                        <td id="T_survival_tablerow38_col4" class="data row38 col4" >1w</td>
                        <td id="T_survival_tablerow38_col5" class="data row38 col5" >1w</td>
                        <td id="T_survival_tablerow38_col6" class="data row38 col6" >1w</td>
                        <td id="T_survival_tablerow38_col7" class="data row38 col7" >1w</td>
                        <td id="T_survival_tablerow38_col8" class="data row38 col8" >1w</td>
                        <td id="T_survival_tablerow38_col9" class="data row38 col9" >1w</td>
                        <td id="T_survival_tablerow38_col10" class="data row38 col10" >1w</td>
                        <td id="T_survival_tablerow38_col11" class="data row38 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row39" class="row_heading level0 row39" >AAH043</th>
                        <td id="T_survival_tablerow39_col0" class="data row39 col0" >25s</td>
                        <td id="T_survival_tablerow39_col1" class="data row39 col1" >5d</td>
                        <td id="T_survival_tablerow39_col2" class="data row39 col2" >1w</td>
                        <td id="T_survival_tablerow39_col3" class="data row39 col3" >1w</td>
                        <td id="T_survival_tablerow39_col4" class="data row39 col4" >16h</td>
                        <td id="T_survival_tablerow39_col5" class="data row39 col5" >1w</td>
                        <td id="T_survival_tablerow39_col6" class="data row39 col6" >1w</td>
                        <td id="T_survival_tablerow39_col7" class="data row39 col7" >1w</td>
                        <td id="T_survival_tablerow39_col8" class="data row39 col8" >6d</td>
                        <td id="T_survival_tablerow39_col9" class="data row39 col9" >1w</td>
                        <td id="T_survival_tablerow39_col10" class="data row39 col10" >2d</td>
                        <td id="T_survival_tablerow39_col11" class="data row39 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row40" class="row_heading level0 row40" >AAH048</th>
                        <td id="T_survival_tablerow40_col0" class="data row40 col0" >20s</td>
                        <td id="T_survival_tablerow40_col1" class="data row40 col1" >1w</td>
                        <td id="T_survival_tablerow40_col2" class="data row40 col2" >15s</td>
                        <td id="T_survival_tablerow40_col3" class="data row40 col3" >5d</td>
                        <td id="T_survival_tablerow40_col4" class="data row40 col4" >35s</td>
                        <td id="T_survival_tablerow40_col5" class="data row40 col5" >1w</td>
                        <td id="T_survival_tablerow40_col6" class="data row40 col6" >20s</td>
                        <td id="T_survival_tablerow40_col7" class="data row40 col7" >1w</td>
                        <td id="T_survival_tablerow40_col8" class="data row40 col8" >20s</td>
                        <td id="T_survival_tablerow40_col9" class="data row40 col9" >1w</td>
                        <td id="T_survival_tablerow40_col10" class="data row40 col10" >20s</td>
                        <td id="T_survival_tablerow40_col11" class="data row40 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row41" class="row_heading level0 row41" >AAH050</th>
                        <td id="T_survival_tablerow41_col0" class="data row41 col0" >25s</td>
                        <td id="T_survival_tablerow41_col1" class="data row41 col1" >5d</td>
                        <td id="T_survival_tablerow41_col2" class="data row41 col2" >6d</td>
                        <td id="T_survival_tablerow41_col3" class="data row41 col3" >6d</td>
                        <td id="T_survival_tablerow41_col4" class="data row41 col4" >29s</td>
                        <td id="T_survival_tablerow41_col5" class="data row41 col5" >1w</td>
                        <td id="T_survival_tablerow41_col6" class="data row41 col6" >1d</td>
                        <td id="T_survival_tablerow41_col7" class="data row41 col7" >1w</td>
                        <td id="T_survival_tablerow41_col8" class="data row41 col8" >28s</td>
                        <td id="T_survival_tablerow41_col9" class="data row41 col9" >1w</td>
                        <td id="T_survival_tablerow41_col10" class="data row41 col10" >29s</td>
                        <td id="T_survival_tablerow41_col11" class="data row41 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row42" class="row_heading level0 row42" >JCH216</th>
                        <td id="T_survival_tablerow42_col0" class="data row42 col0" >2d</td>
                        <td id="T_survival_tablerow42_col1" class="data row42 col1" >5d</td>
                        <td id="T_survival_tablerow42_col2" class="data row42 col2" >1w</td>
                        <td id="T_survival_tablerow42_col3" class="data row42 col3" >1w</td>
                        <td id="T_survival_tablerow42_col4" class="data row42 col4" >1w</td>
                        <td id="T_survival_tablerow42_col5" class="data row42 col5" >1w</td>
                        <td id="T_survival_tablerow42_col6" class="data row42 col6" >1w</td>
                        <td id="T_survival_tablerow42_col7" class="data row42 col7" >1w</td>
                        <td id="T_survival_tablerow42_col8" class="data row42 col8" >1w</td>
                        <td id="T_survival_tablerow42_col9" class="data row42 col9" >1w</td>
                        <td id="T_survival_tablerow42_col10" class="data row42 col10" >1w</td>
                        <td id="T_survival_tablerow42_col11" class="data row42 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row43" class="row_heading level0 row43" >AAH046</th>
                        <td id="T_survival_tablerow43_col0" class="data row43 col0" >3d</td>
                        <td id="T_survival_tablerow43_col1" class="data row43 col1" >6d</td>
                        <td id="T_survival_tablerow43_col2" class="data row43 col2" >1w</td>
                        <td id="T_survival_tablerow43_col3" class="data row43 col3" >1w</td>
                        <td id="T_survival_tablerow43_col4" class="data row43 col4" >1w</td>
                        <td id="T_survival_tablerow43_col5" class="data row43 col5" >1w</td>
                        <td id="T_survival_tablerow43_col6" class="data row43 col6" >1w</td>
                        <td id="T_survival_tablerow43_col7" class="data row43 col7" >1w</td>
                        <td id="T_survival_tablerow43_col8" class="data row43 col8" >1w</td>
                        <td id="T_survival_tablerow43_col9" class="data row43 col9" >1w</td>
                        <td id="T_survival_tablerow43_col10" class="data row43 col10" >1w</td>
                        <td id="T_survival_tablerow43_col11" class="data row43 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row44" class="row_heading level0 row44" >AAH042</th>
                        <td id="T_survival_tablerow44_col0" class="data row44 col0" >40s</td>
                        <td id="T_survival_tablerow44_col1" class="data row44 col1" >6d</td>
                        <td id="T_survival_tablerow44_col2" class="data row44 col2" >24s</td>
                        <td id="T_survival_tablerow44_col3" class="data row44 col3" >1w</td>
                        <td id="T_survival_tablerow44_col4" class="data row44 col4" >1m</td>
                        <td id="T_survival_tablerow44_col5" class="data row44 col5" >1w</td>
                        <td id="T_survival_tablerow44_col6" class="data row44 col6" >45s</td>
                        <td id="T_survival_tablerow44_col7" class="data row44 col7" >1w</td>
                        <td id="T_survival_tablerow44_col8" class="data row44 col8" >40s</td>
                        <td id="T_survival_tablerow44_col9" class="data row44 col9" >1w</td>
                        <td id="T_survival_tablerow44_col10" class="data row44 col10" >45s</td>
                        <td id="T_survival_tablerow44_col11" class="data row44 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row45" class="row_heading level0 row45" >AAH009</th>
                        <td id="T_survival_tablerow45_col0" class="data row45 col0" >21h</td>
                        <td id="T_survival_tablerow45_col1" class="data row45 col1" >6d</td>
                        <td id="T_survival_tablerow45_col2" class="data row45 col2" >4d</td>
                        <td id="T_survival_tablerow45_col3" class="data row45 col3" >1w</td>
                        <td id="T_survival_tablerow45_col4" class="data row45 col4" >5d</td>
                        <td id="T_survival_tablerow45_col5" class="data row45 col5" >1w</td>
                        <td id="T_survival_tablerow45_col6" class="data row45 col6" >6h</td>
                        <td id="T_survival_tablerow45_col7" class="data row45 col7" >1w</td>
                        <td id="T_survival_tablerow45_col8" class="data row45 col8" >2d</td>
                        <td id="T_survival_tablerow45_col9" class="data row45 col9" >1w</td>
                        <td id="T_survival_tablerow45_col10" class="data row45 col10" >2d</td>
                        <td id="T_survival_tablerow45_col11" class="data row45 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row46" class="row_heading level0 row46" >JCH223</th>
                        <td id="T_survival_tablerow46_col0" class="data row46 col0" >16m</td>
                        <td id="T_survival_tablerow46_col1" class="data row46 col1" >6d</td>
                        <td id="T_survival_tablerow46_col2" class="data row46 col2" >32s</td>
                        <td id="T_survival_tablerow46_col3" class="data row46 col3" >1w</td>
                        <td id="T_survival_tablerow46_col4" class="data row46 col4" >1h</td>
                        <td id="T_survival_tablerow46_col5" class="data row46 col5" >1w</td>
                        <td id="T_survival_tablerow46_col6" class="data row46 col6" >5h</td>
                        <td id="T_survival_tablerow46_col7" class="data row46 col7" >1w</td>
                        <td id="T_survival_tablerow46_col8" class="data row46 col8" >2h</td>
                        <td id="T_survival_tablerow46_col9" class="data row46 col9" >1w</td>
                        <td id="T_survival_tablerow46_col10" class="data row46 col10" >11h</td>
                        <td id="T_survival_tablerow46_col11" class="data row46 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row47" class="row_heading level0 row47" >AAH029</th>
                        <td id="T_survival_tablerow47_col0" class="data row47 col0" >15s</td>
                        <td id="T_survival_tablerow47_col1" class="data row47 col1" >6d</td>
                        <td id="T_survival_tablerow47_col2" class="data row47 col2" >20s</td>
                        <td id="T_survival_tablerow47_col3" class="data row47 col3" >1w</td>
                        <td id="T_survival_tablerow47_col4" class="data row47 col4" >15s</td>
                        <td id="T_survival_tablerow47_col5" class="data row47 col5" >1w</td>
                        <td id="T_survival_tablerow47_col6" class="data row47 col6" >15s</td>
                        <td id="T_survival_tablerow47_col7" class="data row47 col7" >1w</td>
                        <td id="T_survival_tablerow47_col8" class="data row47 col8" >15s</td>
                        <td id="T_survival_tablerow47_col9" class="data row47 col9" >1w</td>
                        <td id="T_survival_tablerow47_col10" class="data row47 col10" >15s</td>
                        <td id="T_survival_tablerow47_col11" class="data row47 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row48" class="row_heading level0 row48" >JCH229</th>
                        <td id="T_survival_tablerow48_col0" class="data row48 col0" >4m</td>
                        <td id="T_survival_tablerow48_col1" class="data row48 col1" >6d</td>
                        <td id="T_survival_tablerow48_col2" class="data row48 col2" >24s</td>
                        <td id="T_survival_tablerow48_col3" class="data row48 col3" >1w</td>
                        <td id="T_survival_tablerow48_col4" class="data row48 col4" >24m</td>
                        <td id="T_survival_tablerow48_col5" class="data row48 col5" >1w</td>
                        <td id="T_survival_tablerow48_col6" class="data row48 col6" >2h</td>
                        <td id="T_survival_tablerow48_col7" class="data row48 col7" >1w</td>
                        <td id="T_survival_tablerow48_col8" class="data row48 col8" >49m</td>
                        <td id="T_survival_tablerow48_col9" class="data row48 col9" >1w</td>
                        <td id="T_survival_tablerow48_col10" class="data row48 col10" >2h</td>
                        <td id="T_survival_tablerow48_col11" class="data row48 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row49" class="row_heading level0 row49" >JCH214</th>
                        <td id="T_survival_tablerow49_col0" class="data row49 col0" >35s</td>
                        <td id="T_survival_tablerow49_col1" class="data row49 col1" >1w</td>
                        <td id="T_survival_tablerow49_col2" class="data row49 col2" >54s</td>
                        <td id="T_survival_tablerow49_col3" class="data row49 col3" >1w</td>
                        <td id="T_survival_tablerow49_col4" class="data row49 col4" >1m</td>
                        <td id="T_survival_tablerow49_col5" class="data row49 col5" >1w</td>
                        <td id="T_survival_tablerow49_col6" class="data row49 col6" >40s</td>
                        <td id="T_survival_tablerow49_col7" class="data row49 col7" >1w</td>
                        <td id="T_survival_tablerow49_col8" class="data row49 col8" >35s</td>
                        <td id="T_survival_tablerow49_col9" class="data row49 col9" >1w</td>
                        <td id="T_survival_tablerow49_col10" class="data row49 col10" >42s</td>
                        <td id="T_survival_tablerow49_col11" class="data row49 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row50" class="row_heading level0 row50" >MAE111</th>
                        <td id="T_survival_tablerow50_col0" class="data row50 col0" >18s</td>
                        <td id="T_survival_tablerow50_col1" class="data row50 col1" >1w</td>
                        <td id="T_survival_tablerow50_col2" class="data row50 col2" >15s</td>
                        <td id="T_survival_tablerow50_col3" class="data row50 col3" >1w</td>
                        <td id="T_survival_tablerow50_col4" class="data row50 col4" >15s</td>
                        <td id="T_survival_tablerow50_col5" class="data row50 col5" >1w</td>
                        <td id="T_survival_tablerow50_col6" class="data row50 col6" >20s</td>
                        <td id="T_survival_tablerow50_col7" class="data row50 col7" >1w</td>
                        <td id="T_survival_tablerow50_col8" class="data row50 col8" >20s</td>
                        <td id="T_survival_tablerow50_col9" class="data row50 col9" >1w</td>
                        <td id="T_survival_tablerow50_col10" class="data row50 col10" >20s</td>
                        <td id="T_survival_tablerow50_col11" class="data row50 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row51" class="row_heading level0 row51" >MAE105</th>
                        <td id="T_survival_tablerow51_col0" class="data row51 col0" >15s</td>
                        <td id="T_survival_tablerow51_col1" class="data row51 col1" >1w</td>
                        <td id="T_survival_tablerow51_col2" class="data row51 col2" >15s</td>
                        <td id="T_survival_tablerow51_col3" class="data row51 col3" >1w</td>
                        <td id="T_survival_tablerow51_col4" class="data row51 col4" >15s</td>
                        <td id="T_survival_tablerow51_col5" class="data row51 col5" >1w</td>
                        <td id="T_survival_tablerow51_col6" class="data row51 col6" >15s</td>
                        <td id="T_survival_tablerow51_col7" class="data row51 col7" >1w</td>
                        <td id="T_survival_tablerow51_col8" class="data row51 col8" >15s</td>
                        <td id="T_survival_tablerow51_col9" class="data row51 col9" >1w</td>
                        <td id="T_survival_tablerow51_col10" class="data row51 col10" >15s</td>
                        <td id="T_survival_tablerow51_col11" class="data row51 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row52" class="row_heading level0 row52" >AAH034</th>
                        <td id="T_survival_tablerow52_col0" class="data row52 col0" >15s</td>
                        <td id="T_survival_tablerow52_col1" class="data row52 col1" >1w</td>
                        <td id="T_survival_tablerow52_col2" class="data row52 col2" >15s</td>
                        <td id="T_survival_tablerow52_col3" class="data row52 col3" >1w</td>
                        <td id="T_survival_tablerow52_col4" class="data row52 col4" >15s</td>
                        <td id="T_survival_tablerow52_col5" class="data row52 col5" >1w</td>
                        <td id="T_survival_tablerow52_col6" class="data row52 col6" >15s</td>
                        <td id="T_survival_tablerow52_col7" class="data row52 col7" >1w</td>
                        <td id="T_survival_tablerow52_col8" class="data row52 col8" >15s</td>
                        <td id="T_survival_tablerow52_col9" class="data row52 col9" >1w</td>
                        <td id="T_survival_tablerow52_col10" class="data row52 col10" >15s</td>
                        <td id="T_survival_tablerow52_col11" class="data row52 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row53" class="row_heading level0 row53" >MAE103</th>
                        <td id="T_survival_tablerow53_col0" class="data row53 col0" >33s</td>
                        <td id="T_survival_tablerow53_col1" class="data row53 col1" >1w</td>
                        <td id="T_survival_tablerow53_col2" class="data row53 col2" >1m</td>
                        <td id="T_survival_tablerow53_col3" class="data row53 col3" >1w</td>
                        <td id="T_survival_tablerow53_col4" class="data row53 col4" >33s</td>
                        <td id="T_survival_tablerow53_col5" class="data row53 col5" >1w</td>
                        <td id="T_survival_tablerow53_col6" class="data row53 col6" >40s</td>
                        <td id="T_survival_tablerow53_col7" class="data row53 col7" >1w</td>
                        <td id="T_survival_tablerow53_col8" class="data row53 col8" >34s</td>
                        <td id="T_survival_tablerow53_col9" class="data row53 col9" >1w</td>
                        <td id="T_survival_tablerow53_col10" class="data row53 col10" >31s</td>
                        <td id="T_survival_tablerow53_col11" class="data row53 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row54" class="row_heading level0 row54" >AAH004</th>
                        <td id="T_survival_tablerow54_col0" class="data row54 col0" >16s</td>
                        <td id="T_survival_tablerow54_col1" class="data row54 col1" >1w</td>
                        <td id="T_survival_tablerow54_col2" class="data row54 col2" >15s</td>
                        <td id="T_survival_tablerow54_col3" class="data row54 col3" >1w</td>
                        <td id="T_survival_tablerow54_col4" class="data row54 col4" >15s</td>
                        <td id="T_survival_tablerow54_col5" class="data row54 col5" >1w</td>
                        <td id="T_survival_tablerow54_col6" class="data row54 col6" >15s</td>
                        <td id="T_survival_tablerow54_col7" class="data row54 col7" >1w</td>
                        <td id="T_survival_tablerow54_col8" class="data row54 col8" >15s</td>
                        <td id="T_survival_tablerow54_col9" class="data row54 col9" >1w</td>
                        <td id="T_survival_tablerow54_col10" class="data row54 col10" >15s</td>
                        <td id="T_survival_tablerow54_col11" class="data row54 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row55" class="row_heading level0 row55" >AAH005</th>
                        <td id="T_survival_tablerow55_col0" class="data row55 col0" >15s</td>
                        <td id="T_survival_tablerow55_col1" class="data row55 col1" >1w</td>
                        <td id="T_survival_tablerow55_col2" class="data row55 col2" >15s</td>
                        <td id="T_survival_tablerow55_col3" class="data row55 col3" >1w</td>
                        <td id="T_survival_tablerow55_col4" class="data row55 col4" >15s</td>
                        <td id="T_survival_tablerow55_col5" class="data row55 col5" >1w</td>
                        <td id="T_survival_tablerow55_col6" class="data row55 col6" >15s</td>
                        <td id="T_survival_tablerow55_col7" class="data row55 col7" >1w</td>
                        <td id="T_survival_tablerow55_col8" class="data row55 col8" >15s</td>
                        <td id="T_survival_tablerow55_col9" class="data row55 col9" >1w</td>
                        <td id="T_survival_tablerow55_col10" class="data row55 col10" >15s</td>
                        <td id="T_survival_tablerow55_col11" class="data row55 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row56" class="row_heading level0 row56" >AAH051</th>
                        <td id="T_survival_tablerow56_col0" class="data row56 col0" >25s</td>
                        <td id="T_survival_tablerow56_col1" class="data row56 col1" >1w</td>
                        <td id="T_survival_tablerow56_col2" class="data row56 col2" >15s</td>
                        <td id="T_survival_tablerow56_col3" class="data row56 col3" >1w</td>
                        <td id="T_survival_tablerow56_col4" class="data row56 col4" >42s</td>
                        <td id="T_survival_tablerow56_col5" class="data row56 col5" >1w</td>
                        <td id="T_survival_tablerow56_col6" class="data row56 col6" >25s</td>
                        <td id="T_survival_tablerow56_col7" class="data row56 col7" >1w</td>
                        <td id="T_survival_tablerow56_col8" class="data row56 col8" >25s</td>
                        <td id="T_survival_tablerow56_col9" class="data row56 col9" >1w</td>
                        <td id="T_survival_tablerow56_col10" class="data row56 col10" >30s</td>
                        <td id="T_survival_tablerow56_col11" class="data row56 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row57" class="row_heading level0 row57" >MAE006</th>
                        <td id="T_survival_tablerow57_col0" class="data row57 col0" >15s</td>
                        <td id="T_survival_tablerow57_col1" class="data row57 col1" >1w</td>
                        <td id="T_survival_tablerow57_col2" class="data row57 col2" >15s</td>
                        <td id="T_survival_tablerow57_col3" class="data row57 col3" >1w</td>
                        <td id="T_survival_tablerow57_col4" class="data row57 col4" >15s</td>
                        <td id="T_survival_tablerow57_col5" class="data row57 col5" >1w</td>
                        <td id="T_survival_tablerow57_col6" class="data row57 col6" >15s</td>
                        <td id="T_survival_tablerow57_col7" class="data row57 col7" >1w</td>
                        <td id="T_survival_tablerow57_col8" class="data row57 col8" >15s</td>
                        <td id="T_survival_tablerow57_col9" class="data row57 col9" >1w</td>
                        <td id="T_survival_tablerow57_col10" class="data row57 col10" >1w</td>
                        <td id="T_survival_tablerow57_col11" class="data row57 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row58" class="row_heading level0 row58" >MAE004</th>
                        <td id="T_survival_tablerow58_col0" class="data row58 col0" >15s</td>
                        <td id="T_survival_tablerow58_col1" class="data row58 col1" >1w</td>
                        <td id="T_survival_tablerow58_col2" class="data row58 col2" >15s</td>
                        <td id="T_survival_tablerow58_col3" class="data row58 col3" >1w</td>
                        <td id="T_survival_tablerow58_col4" class="data row58 col4" >15s</td>
                        <td id="T_survival_tablerow58_col5" class="data row58 col5" >1w</td>
                        <td id="T_survival_tablerow58_col6" class="data row58 col6" >15s</td>
                        <td id="T_survival_tablerow58_col7" class="data row58 col7" >1w</td>
                        <td id="T_survival_tablerow58_col8" class="data row58 col8" >15s</td>
                        <td id="T_survival_tablerow58_col9" class="data row58 col9" >1w</td>
                        <td id="T_survival_tablerow58_col10" class="data row58 col10" >1w</td>
                        <td id="T_survival_tablerow58_col11" class="data row58 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row59" class="row_heading level0 row59" >JCH233</th>
                        <td id="T_survival_tablerow59_col0" class="data row59 col0" >8m</td>
                        <td id="T_survival_tablerow59_col1" class="data row59 col1" >1w</td>
                        <td id="T_survival_tablerow59_col2" class="data row59 col2" >23m</td>
                        <td id="T_survival_tablerow59_col3" class="data row59 col3" >1w</td>
                        <td id="T_survival_tablerow59_col4" class="data row59 col4" >6h</td>
                        <td id="T_survival_tablerow59_col5" class="data row59 col5" >1w</td>
                        <td id="T_survival_tablerow59_col6" class="data row59 col6" >11h</td>
                        <td id="T_survival_tablerow59_col7" class="data row59 col7" >1w</td>
                        <td id="T_survival_tablerow59_col8" class="data row59 col8" >1h</td>
                        <td id="T_survival_tablerow59_col9" class="data row59 col9" >1w</td>
                        <td id="T_survival_tablerow59_col10" class="data row59 col10" >5h</td>
                        <td id="T_survival_tablerow59_col11" class="data row59 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row60" class="row_heading level0 row60" >AAH018</th>
                        <td id="T_survival_tablerow60_col0" class="data row60 col0" >41m</td>
                        <td id="T_survival_tablerow60_col1" class="data row60 col1" >1w</td>
                        <td id="T_survival_tablerow60_col2" class="data row60 col2" >5m</td>
                        <td id="T_survival_tablerow60_col3" class="data row60 col3" >1w</td>
                        <td id="T_survival_tablerow60_col4" class="data row60 col4" >5h</td>
                        <td id="T_survival_tablerow60_col5" class="data row60 col5" >1w</td>
                        <td id="T_survival_tablerow60_col6" class="data row60 col6" >1h</td>
                        <td id="T_survival_tablerow60_col7" class="data row60 col7" >1w</td>
                        <td id="T_survival_tablerow60_col8" class="data row60 col8" >1h</td>
                        <td id="T_survival_tablerow60_col9" class="data row60 col9" >1w</td>
                        <td id="T_survival_tablerow60_col10" class="data row60 col10" >1h</td>
                        <td id="T_survival_tablerow60_col11" class="data row60 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row61" class="row_heading level0 row61" >JCH231</th>
                        <td id="T_survival_tablerow61_col0" class="data row61 col0" >21m</td>
                        <td id="T_survival_tablerow61_col1" class="data row61 col1" >1w</td>
                        <td id="T_survival_tablerow61_col2" class="data row61 col2" >35s</td>
                        <td id="T_survival_tablerow61_col3" class="data row61 col3" >1w</td>
                        <td id="T_survival_tablerow61_col4" class="data row61 col4" >2h</td>
                        <td id="T_survival_tablerow61_col5" class="data row61 col5" >1w</td>
                        <td id="T_survival_tablerow61_col6" class="data row61 col6" >5h</td>
                        <td id="T_survival_tablerow61_col7" class="data row61 col7" >1w</td>
                        <td id="T_survival_tablerow61_col8" class="data row61 col8" >5h</td>
                        <td id="T_survival_tablerow61_col9" class="data row61 col9" >1w</td>
                        <td id="T_survival_tablerow61_col10" class="data row61 col10" >11h</td>
                        <td id="T_survival_tablerow61_col11" class="data row61 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row62" class="row_heading level0 row62" >JCH230</th>
                        <td id="T_survival_tablerow62_col0" class="data row62 col0" >4m</td>
                        <td id="T_survival_tablerow62_col1" class="data row62 col1" >1w</td>
                        <td id="T_survival_tablerow62_col2" class="data row62 col2" >41s</td>
                        <td id="T_survival_tablerow62_col3" class="data row62 col3" >1w</td>
                        <td id="T_survival_tablerow62_col4" class="data row62 col4" >1h</td>
                        <td id="T_survival_tablerow62_col5" class="data row62 col5" >1w</td>
                        <td id="T_survival_tablerow62_col6" class="data row62 col6" >5h</td>
                        <td id="T_survival_tablerow62_col7" class="data row62 col7" >1w</td>
                        <td id="T_survival_tablerow62_col8" class="data row62 col8" >1h</td>
                        <td id="T_survival_tablerow62_col9" class="data row62 col9" >1w</td>
                        <td id="T_survival_tablerow62_col10" class="data row62 col10" >5h</td>
                        <td id="T_survival_tablerow62_col11" class="data row62 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row63" class="row_heading level0 row63" >AAH059</th>
                        <td id="T_survival_tablerow63_col0" class="data row63 col0" >20s</td>
                        <td id="T_survival_tablerow63_col1" class="data row63 col1" >1w</td>
                        <td id="T_survival_tablerow63_col2" class="data row63 col2" >15s</td>
                        <td id="T_survival_tablerow63_col3" class="data row63 col3" >1w</td>
                        <td id="T_survival_tablerow63_col4" class="data row63 col4" >17s</td>
                        <td id="T_survival_tablerow63_col5" class="data row63 col5" >1w</td>
                        <td id="T_survival_tablerow63_col6" class="data row63 col6" >20s</td>
                        <td id="T_survival_tablerow63_col7" class="data row63 col7" >1w</td>
                        <td id="T_survival_tablerow63_col8" class="data row63 col8" >20s</td>
                        <td id="T_survival_tablerow63_col9" class="data row63 col9" >1w</td>
                        <td id="T_survival_tablerow63_col10" class="data row63 col10" >20s</td>
                        <td id="T_survival_tablerow63_col11" class="data row63 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row64" class="row_heading level0 row64" >JCH202</th>
                        <td id="T_survival_tablerow64_col0" class="data row64 col0" >15s</td>
                        <td id="T_survival_tablerow64_col1" class="data row64 col1" >1w</td>
                        <td id="T_survival_tablerow64_col2" class="data row64 col2" >15s</td>
                        <td id="T_survival_tablerow64_col3" class="data row64 col3" >1w</td>
                        <td id="T_survival_tablerow64_col4" class="data row64 col4" >15s</td>
                        <td id="T_survival_tablerow64_col5" class="data row64 col5" >1w</td>
                        <td id="T_survival_tablerow64_col6" class="data row64 col6" >15s</td>
                        <td id="T_survival_tablerow64_col7" class="data row64 col7" >1w</td>
                        <td id="T_survival_tablerow64_col8" class="data row64 col8" >15s</td>
                        <td id="T_survival_tablerow64_col9" class="data row64 col9" >1w</td>
                        <td id="T_survival_tablerow64_col10" class="data row64 col10" >15s</td>
                        <td id="T_survival_tablerow64_col11" class="data row64 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row65" class="row_heading level0 row65" >MAE114</th>
                        <td id="T_survival_tablerow65_col0" class="data row65 col0" >15s</td>
                        <td id="T_survival_tablerow65_col1" class="data row65 col1" >1w</td>
                        <td id="T_survival_tablerow65_col2" class="data row65 col2" >15s</td>
                        <td id="T_survival_tablerow65_col3" class="data row65 col3" >1w</td>
                        <td id="T_survival_tablerow65_col4" class="data row65 col4" >15s</td>
                        <td id="T_survival_tablerow65_col5" class="data row65 col5" >1w</td>
                        <td id="T_survival_tablerow65_col6" class="data row65 col6" >15s</td>
                        <td id="T_survival_tablerow65_col7" class="data row65 col7" >1w</td>
                        <td id="T_survival_tablerow65_col8" class="data row65 col8" >15s</td>
                        <td id="T_survival_tablerow65_col9" class="data row65 col9" >1w</td>
                        <td id="T_survival_tablerow65_col10" class="data row65 col10" >15s</td>
                        <td id="T_survival_tablerow65_col11" class="data row65 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row66" class="row_heading level0 row66" >JCH204</th>
                        <td id="T_survival_tablerow66_col0" class="data row66 col0" >26s</td>
                        <td id="T_survival_tablerow66_col1" class="data row66 col1" >1w</td>
                        <td id="T_survival_tablerow66_col2" class="data row66 col2" >24s</td>
                        <td id="T_survival_tablerow66_col3" class="data row66 col3" >1w</td>
                        <td id="T_survival_tablerow66_col4" class="data row66 col4" >48s</td>
                        <td id="T_survival_tablerow66_col5" class="data row66 col5" >1w</td>
                        <td id="T_survival_tablerow66_col6" class="data row66 col6" >30s</td>
                        <td id="T_survival_tablerow66_col7" class="data row66 col7" >1w</td>
                        <td id="T_survival_tablerow66_col8" class="data row66 col8" >26s</td>
                        <td id="T_survival_tablerow66_col9" class="data row66 col9" >1w</td>
                        <td id="T_survival_tablerow66_col10" class="data row66 col10" >30s</td>
                        <td id="T_survival_tablerow66_col11" class="data row66 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row67" class="row_heading level0 row67" >JCH222</th>
                        <td id="T_survival_tablerow67_col0" class="data row67 col0" >1h</td>
                        <td id="T_survival_tablerow67_col1" class="data row67 col1" >1w</td>
                        <td id="T_survival_tablerow67_col2" class="data row67 col2" >39m</td>
                        <td id="T_survival_tablerow67_col3" class="data row67 col3" >1w</td>
                        <td id="T_survival_tablerow67_col4" class="data row67 col4" >4d</td>
                        <td id="T_survival_tablerow67_col5" class="data row67 col5" >1w</td>
                        <td id="T_survival_tablerow67_col6" class="data row67 col6" >6d</td>
                        <td id="T_survival_tablerow67_col7" class="data row67 col7" >1w</td>
                        <td id="T_survival_tablerow67_col8" class="data row67 col8" >2d</td>
                        <td id="T_survival_tablerow67_col9" class="data row67 col9" >1w</td>
                        <td id="T_survival_tablerow67_col10" class="data row67 col10" >5d</td>
                        <td id="T_survival_tablerow67_col11" class="data row67 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row68" class="row_heading level0 row68" >JCH220</th>
                        <td id="T_survival_tablerow68_col0" class="data row68 col0" >4m</td>
                        <td id="T_survival_tablerow68_col1" class="data row68 col1" >1w</td>
                        <td id="T_survival_tablerow68_col2" class="data row68 col2" >20s</td>
                        <td id="T_survival_tablerow68_col3" class="data row68 col3" >1w</td>
                        <td id="T_survival_tablerow68_col4" class="data row68 col4" >22m</td>
                        <td id="T_survival_tablerow68_col5" class="data row68 col5" >1w</td>
                        <td id="T_survival_tablerow68_col6" class="data row68 col6" >1h</td>
                        <td id="T_survival_tablerow68_col7" class="data row68 col7" >1w</td>
                        <td id="T_survival_tablerow68_col8" class="data row68 col8" >46m</td>
                        <td id="T_survival_tablerow68_col9" class="data row68 col9" >1w</td>
                        <td id="T_survival_tablerow68_col10" class="data row68 col10" >2h</td>
                        <td id="T_survival_tablerow68_col11" class="data row68 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row69" class="row_heading level0 row69" >JCH219</th>
                        <td id="T_survival_tablerow69_col0" class="data row69 col0" >3d</td>
                        <td id="T_survival_tablerow69_col1" class="data row69 col1" >1w</td>
                        <td id="T_survival_tablerow69_col2" class="data row69 col2" >1w</td>
                        <td id="T_survival_tablerow69_col3" class="data row69 col3" >1w</td>
                        <td id="T_survival_tablerow69_col4" class="data row69 col4" >6d</td>
                        <td id="T_survival_tablerow69_col5" class="data row69 col5" >1w</td>
                        <td id="T_survival_tablerow69_col6" class="data row69 col6" >1w</td>
                        <td id="T_survival_tablerow69_col7" class="data row69 col7" >1w</td>
                        <td id="T_survival_tablerow69_col8" class="data row69 col8" >1w</td>
                        <td id="T_survival_tablerow69_col9" class="data row69 col9" >1w</td>
                        <td id="T_survival_tablerow69_col10" class="data row69 col10" >1w</td>
                        <td id="T_survival_tablerow69_col11" class="data row69 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row70" class="row_heading level0 row70" >AAH011</th>
                        <td id="T_survival_tablerow70_col0" class="data row70 col0" >15s</td>
                        <td id="T_survival_tablerow70_col1" class="data row70 col1" >1w</td>
                        <td id="T_survival_tablerow70_col2" class="data row70 col2" >15s</td>
                        <td id="T_survival_tablerow70_col3" class="data row70 col3" >1w</td>
                        <td id="T_survival_tablerow70_col4" class="data row70 col4" >15s</td>
                        <td id="T_survival_tablerow70_col5" class="data row70 col5" >1w</td>
                        <td id="T_survival_tablerow70_col6" class="data row70 col6" >15s</td>
                        <td id="T_survival_tablerow70_col7" class="data row70 col7" >1w</td>
                        <td id="T_survival_tablerow70_col8" class="data row70 col8" >15s</td>
                        <td id="T_survival_tablerow70_col9" class="data row70 col9" >1w</td>
                        <td id="T_survival_tablerow70_col10" class="data row70 col10" >15s</td>
                        <td id="T_survival_tablerow70_col11" class="data row70 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row71" class="row_heading level0 row71" >AAH047</th>
                        <td id="T_survival_tablerow71_col0" class="data row71 col0" >2d</td>
                        <td id="T_survival_tablerow71_col1" class="data row71 col1" >1w</td>
                        <td id="T_survival_tablerow71_col2" class="data row71 col2" >1w</td>
                        <td id="T_survival_tablerow71_col3" class="data row71 col3" >1w</td>
                        <td id="T_survival_tablerow71_col4" class="data row71 col4" >16h</td>
                        <td id="T_survival_tablerow71_col5" class="data row71 col5" >1w</td>
                        <td id="T_survival_tablerow71_col6" class="data row71 col6" >1w</td>
                        <td id="T_survival_tablerow71_col7" class="data row71 col7" >1w</td>
                        <td id="T_survival_tablerow71_col8" class="data row71 col8" >6d</td>
                        <td id="T_survival_tablerow71_col9" class="data row71 col9" >1w</td>
                        <td id="T_survival_tablerow71_col10" class="data row71 col10" >2d</td>
                        <td id="T_survival_tablerow71_col11" class="data row71 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row72" class="row_heading level0 row72" >AAH031</th>
                        <td id="T_survival_tablerow72_col0" class="data row72 col0" >20s</td>
                        <td id="T_survival_tablerow72_col1" class="data row72 col1" >1w</td>
                        <td id="T_survival_tablerow72_col2" class="data row72 col2" >22s</td>
                        <td id="T_survival_tablerow72_col3" class="data row72 col3" >1w</td>
                        <td id="T_survival_tablerow72_col4" class="data row72 col4" >42s</td>
                        <td id="T_survival_tablerow72_col5" class="data row72 col5" >1w</td>
                        <td id="T_survival_tablerow72_col6" class="data row72 col6" >20s</td>
                        <td id="T_survival_tablerow72_col7" class="data row72 col7" >1w</td>
                        <td id="T_survival_tablerow72_col8" class="data row72 col8" >20s</td>
                        <td id="T_survival_tablerow72_col9" class="data row72 col9" >1w</td>
                        <td id="T_survival_tablerow72_col10" class="data row72 col10" >25s</td>
                        <td id="T_survival_tablerow72_col11" class="data row72 col11" >1w</td>
            </tr>
            <tr>
                        <th id="T_survival_tablelevel0_row73" class="row_heading level0 row73" >AAH054</th>
                        <td id="T_survival_tablerow73_col0" class="data row73 col0" >10s</td>
                        <td id="T_survival_tablerow73_col1" class="data row73 col1" >1w</td>
                        <td id="T_survival_tablerow73_col2" class="data row73 col2" >10s</td>
                        <td id="T_survival_tablerow73_col3" class="data row73 col3" >1w</td>
                        <td id="T_survival_tablerow73_col4" class="data row73 col4" >10s</td>
                        <td id="T_survival_tablerow73_col5" class="data row73 col5" >1w</td>
                        <td id="T_survival_tablerow73_col6" class="data row73 col6" >10s</td>
                        <td id="T_survival_tablerow73_col7" class="data row73 col7" >1w</td>
                        <td id="T_survival_tablerow73_col8" class="data row73 col8" >10s</td>
                        <td id="T_survival_tablerow73_col9" class="data row73 col9" >1w</td>
                        <td id="T_survival_tablerow73_col10" class="data row73 col10" >10s</td>
                        <td id="T_survival_tablerow73_col11" class="data row73 col11" >1w</td>
            </tr>
    </tbody></table>
    </div>
</div>



{% endcapture %}
{{ template | replace: '    ', ''}}