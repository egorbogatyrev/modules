<?php

/**
 * @file
 * Contains MedsReport interface.
 */

/**
 * The interface for export format.
 */
interface PerformanceTestInterface {

  /**
   * The report machine name.
   */
  public static function testMachineName();

  /**
   * Returns a permission for the report.
   */
  public function testPermission();

  /**
   * The report description.
   */
  public function testDescription();

  /**
   * The callback function with used to export results to a file.
   */
  public function exportCallback();

  /**
   * Each of test can specify a category where it will be appeared.
   */
  public function reportCategory();
}
