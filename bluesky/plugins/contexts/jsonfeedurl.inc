<?php

/**
 *
 * Plugin to provide a mechanism for specifying a JSON feed URL
 */

/**
 * Plugins are described by creating a $plugin array which will be 
 * used by the system that includes this file
 */
$plugin = array(
	'title' => t('JSON Feed URL'),
	'description' => t('A JSON Feed URL'),
	'context' => 'bluesky_arg_create_json_feed',
	'edit form' => 'bluesky_arg_jsonfeedurl_settings_form',
	'defaults' => array('json_feed_url' => ''),
	'keyword' => 'json_feed_url',
	'context name' => 'jsonfeedurl',
);

function bluesky_arg_create_jsonfeedurl($arg = NULL, $conf = NULL, $empty) {
	$context = new ctools_context('jsonfeedurl');
	$context->plugin = 'jsonfeedurl';

	return $context;
}

function bluesky_arg_jsonfeedurl_settings_form($form, &$form_state) {
	$conf = $form_state['conf'];

	$form['jsonfeedurl'] = array('#type' => 'textfield',
		'#title' => t('JSON Feed URL'),
		'#required' => TRUE,
		'#description' => t('Specify the URL for the JSON data source'),
	);

	return $form;
}

function bluesky_arg_jsonfeedurl_settings_form_submit($form, &$form_state) {
	kpr(array_keys($form_state));
	$form_state['conf']['jsonfeedurl'] = $form_state['values']['jsonfeedurl'];
}

