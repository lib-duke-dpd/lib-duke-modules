<?php

/**
 * @file
 * Default theme implementation to present the 'ALL' tab content for 
 * the Frontpage Search Box.
 *
 * Available variables:
 * - $config: Contents/definition TBD.
 *
 * @see template_preprocess()
 * @see template_preprocess_aggregator_summary_item()
 *
 * @ingroup themeable
 */
?>
<div class="searchBoxContent" id="allTabContent" style="display:block">
	<div class="tabContentUpper">
		<form name="quickSearch" method="get" action="http://duke.summon.serialssolutions.com/search">
			<p class="searchOptionsPrimary">
				<input type="hidden" id="r_yes" name="keep_r" value="true">
				<input class="hasHint styledSearchBox" name="s.q" size="55" title="Search for articles, books, journals &#38; more" type="text" value="" />
				<input class="styledSearchButton" alt="Enter a search term and click on 'Search' to get results" onclick="pageTracker._trackEvent('homepageSearchBox', 'allSearch');" title="Enter a search term and click on 'Search' to get results" type="submit" value="Search" />
				<input class="styledSearchButton_small" alt="Enter a search term and click on 'Go' to get results" onclick="pageTracker._trackEvent('homepageSearchBox', 'allSearch');" title="Enter a search term and click on 'Go' to get results" type="submit" value="GO" />
			</p>
			<p class="checkboxes">
				<span class="allTabCheckboxes">
					<label class="bold">Include in results:</label> &#160;&#160;
					<input type="checkbox" id="check_newspaper" value="" /><label for="check_newspaper">Newspaper articles</label> &#160;&#160;
					<input type="checkbox" id="check_bookreviews" value="" /><label for="check_bookreviews">Book reviews</label>
					<input id="summon_newspaper" name="s.fvf[]" checked="checked" type="checkbox" value="ContentType,Newspaper Article,t" style="display:none;"/>
					<input id="summon_bookreviews" name="s.fvf[]" checked="checked" type="checkbox" value="ContentType,Book Review,t" style="display:none;"/>
				</span>
				<span class="whatSearch">
					<a onclick="pageTracker._trackEvent('homepageSearchBox', 'whatIsAllSearch');" href="javascript:unhide('whatAll');">
						<strong>About ALL</strong>
					</a>
				</span>
			</p>
		</form>
	</div><!-- /tabContentUpper -->
	<div class="toggleClosed" id="whatAll">
		<p><strong>What am I searching when I use the ALL tab?</strong></p>
		<ul>
			<li>Most of the journal articles available through Duke University Libraries</li>
			<li>All the books, films, music, special collections, ebooks, database titles and more from our catalog</li>
			<li><a href="http://library.duke.edu/research/subject/index.html">Research guides</a> to library resources</li>
			<li>Content from Duke authors in the <a href="http://library.duke.edu/dukespace/">open access repository</a></li>
		</ul>
		<p>
			<strong>Note:</strong> Newspaper articles and book reviews are excluded by default. Click the check boxes to change these search parameters.
		</p>
		<p>
			<a href="http://library.duke.edu/research/tools/all-tab.html">Learn more at the Search Tips page >></a>
		</p>
		<div class="closeWhat">
			<div class="closeWhatButton">
				<a onclick="pageTracker._trackEvent('homepageSearchBox', 'closeWhat');" href="javascript:unhide('whatAll');">&#160;Close X&#160;</a>
			</div>
		</div>
	</div>
	<div class="tabContentLower">
		<p class="searchOptionsTertiary">
			<a href="https://duke.qualtrics.com/SE/?SID=SV_4TrJkYnDP8isWPO" target="_blank" onclick="window.open(this.href, this.target,'height=725px,width=550px,status=1,menubar=1,resizable=1,scrollbars=1'); return false" title="Tell us what you think about the All tab"><span style="font-weight: bold; color: red;">Feedback</span></a> &nbsp;|&nbsp; <a onclick="pageTracker._trackEvent('homepageSearchBox', 'allSearchTips');" href="http://library.duke.edu/research/tools/all-tab.html">Search Tips</a> &nbsp;|&nbsp; <a onclick="pageTracker._trackEvent('homepageSearchBox', 'allSearchAdvanced');" href="http://duke.summon.serialssolutions.com/advanced">Advanced Search</a>
		</p>
	</div> <!-- /tabContentLower -->
</div> <!-- /allTabContent -->
