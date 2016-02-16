<?php

/**
 * @file
 * Contains MedsReportsNewUser class which used to get information about
 * new users in the meds system.
 */

$plugin = array(
  'name' => 'Theme',
  'description' => 'Provides the test to compare render performance.',
  'handler' => array(
    'class' => 'PerformanceTestRender',
  ),
);

class PerformanceTestRender implements PerformanceTestInterface {
  const CREATED_DATE_FORMAT = 'Y-m-d';

  /**
   * The plugin definition for this instance.
   */
  protected $plugin;

  /**
   * Constructor for the report plugin class.
   */
  public function __construct($plugin) {
    $this->plugin = $plugin;
  }

  /**
   * The report machine name.
   */
  public static function testMachineName() {

  }

  /**
   * Returns a permission for the report.
   */
  public function testPermission() {

  }

  /**
   * The report description.
   */
  public function testDescription() {

  }

  /**
   * The callback function with used to export results to a file.
   */
  public function exportCallback() {

  }

  /**
   * Each of test can specify a category where it will be appeared.
   */
  public function reportCategory() {

  }
}
