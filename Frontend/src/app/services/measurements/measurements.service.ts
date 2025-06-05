import { Injectable } from '@angular/core';
import { ApiService } from '../api/api.service';

@Injectable({
  providedIn: 'root',
})
export class MeasurementsService {
  constructor(private apiService: ApiService) {}

  async getToday() {
    const today = await this.apiService.fetchMeasurements('today/kwh');
    return today;
  }

  async getWeek() {
    const week = await this.apiService.fetchMeasurements('this-week/kwh');
    return week;
  }

  async getSevenDays() {
    const sevenDays = await this.apiService.fetchMeasurements('last-7-days/kwh');
    return sevenDays;
  }
}
