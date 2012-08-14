<?php

require_once "inc/gapi/apiClient.php";
require_once "inc/gapi/contrib/apiCalendarService.php";

function newApiCalendarService()
{
	date_default_timezone_set('America/New_York');
	$apiClient = new apiClient();
	$apiClient->setUseObjects(true);
	$service = new apiCalendarService($apiClient);

	return $service;
}
