<?php

?>
<div class="searchBoxContent" id="catalogTabContent" style="display:none">
	<div class="tabContentUpper">
		<form action="http://search.library.duke.edu/search" method="get" name="searchCatalog">
			<!-- HIDDEN input elements -->
			<input type="hidden" name="sugg" id="catalogsuggestions" value="" />
			<input type="hidden" name="source" id="catalogsource" value="duke" />
			<input type="hidden" name="Nty" value="1" />
			<input type="hidden" name="N" value="0" />

			<p class="searchOptionsPrimary">
				<select id="catalogcodeinput" name="Ntk">
					<option selected="selected" value="Keyword">Keywords</option>
					<option value="Title">Title</option>
					<option value="Author">Author</option>
					<option value="Subject">Subject Heading</option>
					<option value="ISBN">ISBN/ISSN</option>
					<option value="Call Number">Call Number</option>
				</select>
				<input class="hasHint styledSearchBox" id="catalogqueryinput" name="Ntt" size="38" title="Search for books, journals, films &#38; more" type="text" value="" />
				<input class="styledSearchButton" alt="Search" onclick="pageTracker._trackEvent('homepageSearchBox', 'catalogSearch');" id="catalogsubmit" title="Enter a search term and click on 'Search' to get catalog results" type="submit" value="Search" />
				<input class="styledSearchButton_small" alt="Search" onclick="pageTracker._trackEvent('homepageSearchBox', 'catalogSearch');" id="catalogsubmit" title="Enter a search term and click on 'Go' to get catalog results" type="submit" value="GO" />
			</p>
		</form>
		<p class="whatSearch">
			<a onclick="pageTracker._trackEvent('homepageSearchBox', 'whatIsCatalogSearch');" href="javascript:unhide('whatCatalog');">
				<strong>About Catalog</strong>
			</a>
		</p>
	</div> <!-- /tabContentUpper -->
	<div class="toggleClosed" id="whatCatalog">
		<p><strong>What am I searching when I use the Catalog tab?</strong></p>
		<ul>
		<!-- <li>Searches what was previously called "Catalog"</li> -->
			<li>Includes books, eBooks, journal titles, music and film</li>
			<li>Includes special collections and University Archives materials</li>
		</ul>
		<p>
			<a onclick="pageTracker._trackEvent('homepageSearchBox', 'learnCatalog');" href="http://library.duke.edu/research/help/catalog/index.html">Learn more at the Catalog Help page >></a>
		</p>
		<div class="closeWhat">
		<div class="closeWhatButton">
			<a onclick="pageTracker._trackEvent('homepageSearchBox', 'closeWhat');" href="javascript:unhide('whatCatalog');">&#160;Close X&#160;</a></div>
		</div>
	</div>
	<div class="tabContentLower">
		<p class="searchOptionsTertiary">
			<a onclick="pageTracker._trackEvent('homepageSearchBox', 'catalogEbooks');" href="http://getitatduke.library.duke.edu/?L=PM6MT7VG3J&tab=BOOKS">eBooks</a> &nbsp;|&nbsp; <a onclick="pageTracker._trackEvent('homepageSearchBox', 'catalogAdvanced');" href="http://library.duke.edu/catalog/advanced">Advanced Search</a> &nbsp;|&nbsp; <a onclick="pageTracker._trackEvent('homepageSearchBox', 'catalogClassic');" href="http://catalog.library.duke.edu/">Classic Catalog</a> &nbsp;|&nbsp; <a onclick="pageTracker._trackEvent('homepageSearchBox', 'catalogTRLN');" href="http://search.trln.org" title="Search UNC, NCSU, NCCU catalogs. Borrow through Interlibrary Loan.">Search TRLN</a> &nbsp;|&nbsp; <a onclick="pageTracker._trackEvent('homepageSearchBox', 'worldcat');" href="http://library.duke.edu/metasearch/db/id/DUK00852" title="Search WorldCat. Available to Duke community only.">WorldCat</a>
		</p>
	</div> <!-- /tabContentLower -->
</div> <!-- /catalogTabContent -->
