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
	'title' => t('Simile Exhibit'),
	'description' => t('Context to alert page to use Simile Widget'),
	'context' => 'bluesky_arg_create_simile_exhibit',
	'edit form' => 'bluesky_arg_simile_exhibit_settings_form',
	'defaults' => array('json_feed_url' => ''),
	'keyword' => 'simile_exhibit',
	'context name' => 'simile_exhibit',
);

function bluesky_arg_create_simile_exhibit($arg = NULL, $conf = NULL, $empty) {
	$context = new ctools_context('simile_exhibit');
	$context->plugin = 'simile_exhibit';

	return $context;
}

function bluesky_arg_simile_exhibit_settings_form($form, &$form_state) {
	$conf = &$form_state['conf'];

	$form['jsonfeedurl'] = array('#type' => 'textfield',
		'#title' => t('JSON Feed URL'),
		'#required' => TRUE,
		'#description' => t('Specify the URL for the JSON data source'),
		'#value' => $conf['jsonfeedurl'],
	);

	return $form;
}

function bluesky_arg_simile_exhibit_settings_form_submit($form, &$form_state) {
	watchdog('settings_form_submit', print_r($form_state, TRUE));
	$form_state['conf']['jsonfeedurl'] = $form_state['values']['jsonfeedurl'];
}

